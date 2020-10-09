#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

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
        } catch (const std::bad_alloc& e) {
          std::cout << "Allocation failed: " << e.what() << '\n';
          begin = nullptr;
        }
        fullSize = maxSize;
      } else {
        std::cout << "You already have an allocator!\n";
      }
    }

    char* alloc(size_t size) {
      if (size + current > fullSize) {
        return nullptr;
      }
      current += size;
      char *temp = begin + current;
      return temp;
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
