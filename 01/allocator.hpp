#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <cstddef>
#include <iostream>

class Allocator {
  private:
    char* begin;
    size_t fullSize;
    size_t current;

  public:
    Allocator():
      begin(nullptr),
      fullSize(0),
      current(0) {}

    void makeAllocator(size_t maxSize) {
      if (begin == nullptr) {
        try {
          begin = new char[maxSize];
          fullSize = maxSize;
        } catch (const std::bad_alloc& e) {
          std::cout << "Allocation failed: " << e.what() << '\n';
          begin = nullptr;
        }
      } else {
        std::cout << "You already have an allocator!\n";
      }
    }

    char* alloc(size_t size) {
      if ((size + current > fullSize) || (size < 1)) {
        return nullptr;
      }
      char *temp = begin + current;
      current += size;
      return temp;
    }

    char* get_ptr_by_offset(size_t size) {
      return begin + size;
    }

    void reset() {
      current = 0;
    }

    ~Allocator() {
      current = 0;
      fullSize = 0;
      delete [] begin;
    }
};

#endif  // ALLOCATOR_H_
