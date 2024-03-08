#ifndef HPP2024_LRU_CACHE_HPP
#define HPP2024_LRU_CACHE_HPP

#include <iosfwd>
#include <cstddef>

#include <queue>
#include <unordered_map>


namespace cache {
    class LruCache {
      public:
        LruCache(const ptrdiff_t size);
        ~LruCache() noexcept;
        
        // search and insert page in cache
        // return page
        std::string cache_lookup_update(const ptrdiff_t key);

      private:
        ptrdiff_t size_;
        std::queue<ptrdiff_t> recent_pages_;
        std::unordered_map<ptrdiff_t, std::string> cache_; 
    };
};

#endif HPP2024_LRU_CACHE_HPP
