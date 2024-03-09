#ifndef HPP2024_LRU_CACHE_HPP
#define HPP2024_LRU_CACHE_HPP

#include <queue>
#include <unordered_map>

#include "book.hpp"


namespace cache {
    class LruCache {
      public:
        LruCache(const ptrdiff_t size);
        ~LruCache() noexcept;
        // search and insert page in cache
        // return page
        std::string cache_lookup_update(const book::Book& book, const ptrdiff_t key);

        ptrdiff_t size_;
        std::queue<ptrdiff_t> recent_pages_;
        std::unordered_map<ptrdiff_t, std::string> cache_; 
    };
};

#endif HPP2024_LRU_CACHE_HPP
