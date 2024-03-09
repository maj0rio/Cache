cmake_minimum_required(VERSION 3.14)
project(caches)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
include_directories(book)
include_directories(lru_cache)

add_subdirectory(book)
add_subdirectory(lru_cache)

target_link_libraries(lru_cache book)

add_subdirectory(tests)