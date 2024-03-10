#ifndef CPP2024_LRU_CACHE_CPP
#define CPP2024_LRU_CACHE_CPP

#include <iostream>
#include <stdexcept>
#include <random>
#include <unistd.h>

#include "lru_cache.hpp"
#include "book.hpp"


const std::string* slow_get_page(const book::Book& book, const ptrdiff_t key) {
    sleep(2);
    return book.slow_load(key);
}

cache::LruCache::LruCache(const ptrdiff_t size) {
    if (size < 0)
        throw std::invalid_argument("Size must be positive!");
    size_ = size;
}

cache::LruCache::~LruCache() noexcept {
    Node* current = recent_pages_.front();
    while (current != nullptr) {
        Node* next = current->next;
        delete current; 
        current = next;
    }
    recent_pages_.clear();
    cache_.clear();
    size_ = 0;
}

cache::LruCache::Node* cache::LruCache::move_front(cache::LruCache::Node* ptr) {
    if (ptr != recent_pages_.front()) {
        Node* prev = ptr->prev;
        Node* next = ptr->next;

        if (next != nullptr)
            next->prev = prev;

        Node* new_ptr = new Node{nullptr, recent_pages_.front(), ptr->number, ptr->page};
        if (recent_pages_.front() != nullptr)
            recent_pages_.front()->prev = new_ptr;
        recent_pages_.push_front(new_ptr);

        auto current = recent_pages_.begin();
        while (current != recent_pages_.end() && *current != ptr)
            current++;
        if (current != recent_pages_.end())
            recent_pages_.erase(current);
    }
    return recent_pages_.front();
} 

const std::string* cache::LruCache::cache_lookup_update(const book::Book& book, const ptrdiff_t key) {
    bool found_in_cache = true;
    if (cache_.find(key) == cache_.end()) {
        found_in_cache = false;
    }

    if (!found_in_cache) {
        if (recent_pages_.size() == size_) {
            ptrdiff_t deleted_key = recent_pages_.back()->number;
            recent_pages_.pop_back();
            cache_.erase(deleted_key);
        }
        const std::string* page = slow_get_page(book, key);  
        Node* new_page = new Node{nullptr, recent_pages_.front(), key, page};
        if (recent_pages_.front() != nullptr)
            recent_pages_.front()->prev = new_page;
        recent_pages_.push_front(new_page);
        cache_[key] = new_page;
    }
    Node* cache_ptr = cache_[key]; 
    auto front_list = move_front(cache_ptr);
    return front_list->page;
}


#endif HPP2024_LRU_CACHE_HPP