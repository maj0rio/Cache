#ifndef CPP2024_BOOK_CPP
#define CPP2024_BOOK_CPP

#include <stdexcept>

#include <random>
#include <unordered_map>

#include <book.hpp>


std::string generate_random_string(int n) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, charset.size() - 1);
    for (size_t i = 0; i < n; ++i) {
        result += charset[dis(gen)];
    }
    return result;
}

book::Book::Book(const ptrdiff_t size) {
    if (size <= 0)
        throw std::invalid_argument("Size must be positive!");
    
    size_ = size;
    for (size_t page = 1; page <= size; ++page) {
        std::string random_string = generate_random_string(5 + rand() % 11);
        pages[page] = random_string;
    }
}

const std::string* book::Book::slow_load(const ptrdiff_t key) const {
    if (key <= 0 || key > size_)
        throw std::out_of_range("");
    return &pages.at(key);
}

#endif CPP2024_BOOK_CPP
