#ifndef CPP2024_LRU_CACHE_CPP
#define CPP2024_LRU_CACHE_CPP

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
    while (!recent_pages_.empty()) {
        recent_pages_.pop();
    }
    cache_.clear();
    size_ = 0;
}

std::string cache::LruCache::cache_lookup_update(const book::Book& book, const ptrdiff_t key) {
    bool found_in_cache = true;
    if (cache_.find(key) == cache_.end()) {
        found_in_cache = false;
    }
    if (recent_pages_.size() == size_) {
        ptrdiff_t last_used_page = recent_pages_.front();
        cache_.erase(last_used_page);
        recent_pages_.pop();
    }
    if (!found_in_cache) {
        cache_[key] = *slow_get_page(book, key);
    }
    recent_pages_.push(key);
    return cache_[key];
}


#endif HPP2024_LRU_CACHE_HPP
