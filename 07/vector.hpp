#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>
#include <memory>
#include <iostream>
#include <iterator>

template <class T>
class Iterator : public std::iterator <std::random_access_iterator_tag, T> {
  private:
    T* current_;

  public:
    explicit Iterator(T* ptr)
      : current_(ptr) {}

     bool operator==(const Iterator<T>& other) const {
       return current_ == other.current_;
     }

     bool operator!=(const Iterator<T>& other) const {
       return !(*this == other);
     }

     Iterator& operator++() {
       current_++;
       return *this;
     }

     Iterator& operator--() {
       current_--;
       return *this;
     }

     T& operator*() const {
       return *current_;
     }
};


template<class T>
class Allocator {
  public:
    T* allocate(size_t size) {
      return static_cast<T*> (malloc(sizeof(T) * size));
    }

    template <class... Args>
    void construct(T* newData, Args&&... args) {
      new(newData) T(std::forward<Args>(args)...);
    }

    void deallocate(T* data) {
      free(data);
    }

    void destroy(T* ptr) {
      ptr->~T();
    }
};

template<class T, class Allocator = Allocator<T>>
class Vector {
  public:
    using reverse_iterator = class std::reverse_iterator<Iterator<T>>;
    using iterator = Iterator<T>;

  private:
    size_t size_;
    size_t capacity_;
    T* data_;
    Allocator allocator_;

  public:
    Vector():
      size_(0),
      capacity_(0),
      data_(allocator_.allocate(0)) { }

    explicit Vector(const size_t size):
      size_(size),
      capacity_(size),
      data_(allocator_.allocate(size)) { }

    Vector(const Vector& other) {
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = allocator_.allocate(other.capacity_);
      for (size_t i = 0; i < other.size_; i++) {
        data_[i] = other.data_[i];
      }
    }

    Vector(Vector&& other) {
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = other.data_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    Vector& operator=(const Vector& other) {
      allocator_.deallocate(data_);
      capacity_ = other.capacity_;
      data_ = allocator_.allocate(other.capacity_);
      for (size_t i = 0; i < other.size_; i++) {
        data_[i] = other.data_[i];
      }
      return *this;
    }

    Vector& operator=(Vector&& other) {
      allocator_.deallocate(data_);
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = other.data_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
      return *this;
    }

    void reserve(size_t size) {
      T* newData = allocator_.allocate(size);
      for (size_t i = 0; i < size_; i++) {
        allocator_.construct(newData + i, std::move(data_[i]));
        allocator_.destroy(data_ + i);
      }
      allocator_.deallocate(data_);
      data_ = newData;
      capacity_ = size;
    }

    T& operator[](size_t i) {
      if (i < size_) {
        return data_[i];
      } else {
        throw std::out_of_range("out of range");
      }
    }

    const T& operator[](size_t i) const {
      if (i < size_) {
        return data_[i];
      } else {
        throw std::out_of_range("out of range");
      }
    }

    void push_back(const T& element) {
      if (size_ + 1 > capacity_) {
        reserve((size_ + 1) * 2);
      }
      allocator_.construct(data_ + size_, element);
      size_++;
    }

    void push_back(T&& element) {
      if (size_ + 1 > capacity_) {
        reserve((size_ + 1) * 2);
      }
      allocator_.construct(data_ + size_, std::move(element));
      size_++;
    }

    template <class... Args>
    void emplace_back(Args&& ... args) {
      if (size_ + 1 > capacity_) {
        reserve((size_ + 1) * 2);
      }
      allocator_.construct(data_ + size_, std::forward<Args>(args)...);
      size_++;
    }

    void pop_back() {
      if (size_ > 0) {
        allocator_.destroy(data_ + size_);
        size_--;
      }
    }

    bool empty() {
      return (size_ == 0);
    }

    size_t size() {
      return size_;
    }

    size_t capacity() {
      return capacity_;
    }

    void resize(size_t newSize) {
      if (newSize > size_) {
        if (newSize >= capacity_) {
          allocator_.reserve(newSize);
        }
        for (T* i = size_ + 1; i < newSize; i++) {
          allocator_.construct(std::move(i));
        }
      }
      if (newSize < size_) {
        for (T* i = data_ + size_; i > data_ + newSize; i--) {
          allocator_.destroy(i);
        }
      }
      size_ = newSize;
    }

    iterator begin() noexcept {
      return iterator(data_);
    }

    reverse_iterator rbegin() noexcept {
      return reverse_iterator(end());
    }

    iterator end() noexcept {
      return iterator(data_ + size_);
    }

    reverse_iterator rend() noexcept {
      return reverse_iterator(begin());
    }

    void clear() {
      for (size_t i = 0; i < size_; ++i) {
        allocator_.destroy(data_ + i);
      }
      size_ = 0;
    }

    ~Vector() {
      this->clear();
      allocator_.deallocate(data_);
      size_ = 0;
      capacity_ = 0;
    }
};
#endif  // VECTOR_HPP
