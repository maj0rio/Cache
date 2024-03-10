#include <gtest/gtest.h>
#include <chrono> // for time tests 


#include "book.hpp"
#include "lru_cache.hpp"

class LruCacheTest : public testing::Test {
  protected:
    book::Book b{10};
    cache::LruCache cache{5};
};

TEST_F(LruCacheTest, BookSize) {
    EXPECT_EQ(b.size_, 10) << "Size" << b.size_;
    std::unordered_map<ptrdiff_t, std::string> values = b.pages;
    EXPECT_EQ(values.size(), 10);
}

TEST_F(LruCacheTest, BookNegativeSize) {
    EXPECT_THROW(book::Book(-1), std::invalid_argument);
    EXPECT_THROW(book::Book(0), std::invalid_argument);
}

TEST_F(LruCacheTest, CacheSize) {
    EXPECT_EQ(cache.size_, 5);
    EXPECT_EQ(cache.recent_pages_.size(), 0);
    EXPECT_EQ(cache.cache_.size(), 0);
}

TEST_F(LruCacheTest, CacheWork) {
    int key = 1;
    cache.cache_lookup_update(b, 1);
    EXPECT_EQ(cache.cache_.size(), 1);
    EXPECT_EQ(cache.recent_pages_.size(), 1);
    std::unordered_map<ptrdiff_t, cache::LruCache::Node*>& pages = cache.cache_;
    
    
    EXPECT_EQ(pages[key]->page, &b.pages[key]);
    EXPECT_EQ(cache.recent_pages_.front()->number, key);

    auto start_time = std::chrono::steady_clock::now();
    const std::string* result = cache.cache_lookup_update(b, 1);
    EXPECT_EQ(result, &b.pages[1]);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    EXPECT_LT(duration.count(), 1);

    key = 2;
    cache.cache_lookup_update(b, key);
    EXPECT_EQ(*pages[key]->page, b.pages[key]);
    EXPECT_EQ(cache.recent_pages_.back()->number, 1);
    EXPECT_EQ(cache.recent_pages_.size(), 2);

    start_time = std::chrono::steady_clock::now();
    key = 3;
    cache.cache_lookup_update(b, key);
    end_time = std::chrono::steady_clock::now();
    int64_t  d = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    EXPECT_GT(d, 1000);

    EXPECT_EQ(pages[key]->page, &b.pages[key]) << pages[key]->page << " " << &b.pages[key];
    EXPECT_EQ(cache.recent_pages_.back()->number, 1) << cache.recent_pages_.back()->number;
    EXPECT_EQ(cache.recent_pages_.front()->number, 3) << cache.recent_pages_.front()->number;
    EXPECT_EQ(cache.recent_pages_.size(), 3);
    EXPECT_EQ(pages.size(), 3);


    start_time = std::chrono::steady_clock::now();
    key = 1;
    cache.cache_lookup_update(b, key);
    end_time = std::chrono::steady_clock::now();
    d = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    EXPECT_LT(d, 1000) << d << " ADKPADKPAD";

    EXPECT_EQ(pages[key]->number, 1) << pages[key]->number << " " << key;
    EXPECT_EQ(pages[key]->page, &b.pages[key]);
    EXPECT_EQ(cache.recent_pages_.front()->number, 1);
    EXPECT_EQ(cache.recent_pages_.back()->number, 2);
    EXPECT_EQ(cache.recent_pages_.size(), 3) << cache.recent_pages_.front()->number << "\n "
                                             << cache.recent_pages_.back()->number;
    EXPECT_EQ(pages.size(), 3);
}