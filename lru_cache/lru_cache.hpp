#ifndef HPP2024_LRU_CACHE_HPP
#define HPP2024_LRU_CACHE_HPP

#include <list>
#include <unordered_map>

#include "book.hpp"


namespace cache {
    class LruCache {
      public:
        LruCache(const ptrdiff_t size);
        ~LruCache() noexcept;
        // search and insert page in cache
        // return page
        const std::string* cache_lookup_update(const book::Book& book, const ptrdiff_t key);

        struct Node {
          Node* prev;
          Node* next;
          ptrdiff_t number;
          const std::string* page;
        };

        ptrdiff_t size_;
        std::list<Node*> recent_pages_; 
        std::unordered_map<ptrdiff_t, Node*> cache_; 
      private:
        Node* move_front(Node* key);
    };
};

#endif HPP2024_LRU_CACHE_HPP
