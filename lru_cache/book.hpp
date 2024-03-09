#ifndef HPP2024_BOOK_HPP
#define HPP2024_BOOK_HPP

#include <iosfwd>
#include <unordered_map>


namespace book {
    class Book {
      public:
        Book(const ptrdiff_t size);
        const std::string* slow_load(const ptrdiff_t key) const;

      private:
        ptrdiff_t size_;
        std::unordered_map<ptrdiff_t, std::string> pages;
    };
}

#endif HPP2024_BOOK_HPP
