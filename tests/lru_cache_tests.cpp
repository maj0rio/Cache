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
    std::unordered_map<ptrdiff_t, std::string>& pages = cache.cache_;

    EXPECT_EQ(pages[key], b.pages[key]);
    EXPECT_EQ(cache.recent_pages_.front(), key);

    auto start_time = std::chrono::steady_clock::now();
    std::string result = cache.cache_lookup_update(b, 1);
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

    EXPECT_LE(duration.count(), 1);

}