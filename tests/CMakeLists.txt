enable_testing()

add_executable(
  cache_test
  lru_cache_tests.cpp
)

target_link_libraries(
  cache_test
  lru_cache
  book
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cache_test)