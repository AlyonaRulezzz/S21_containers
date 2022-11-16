//  47 min ??
// выде

#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include "iterators/vector_iterator.h"
#include <initializer_list>
#include <stdexcept>

using std::out_of_range;

namespace s21 {
// template <typename T, class Allocator = std::allocator<T>> class Vector {
template <typename T> class Vector {
public:
  using value_type = T;
  // using allocator_type = Allocator;
  using reference = T &;
  using const_reference = const T &;
  // using pointer = T *;                           // really needed?
  using iterator = T *;
  // using iterator = VectorIterator<T>;            // equal T*
  // using const_iterator = VectorConstIterator<T>; // equal const T*
  using const_iterator = const T *;
  using size_type = size_t;

private:
  size_type size_;
  size_type capacity_;
  iterator arr_;
  // allocator_type allocator_;

  // void remove_vector_() {  //  exactly equal ~Vector()
  // if (arr_) {
  //   CleanMemory_();
  // }
  // size_ = 0;
  // capacity_ = 0;
  // arr_ = nullptr;
  // }

public:
  // additional functions
  // size_type GetSize() const {return size_; }
  // size_type GetCapacity() const {return capacity_; }
  // iterator GetArr() const {return arr_; }

  // functions (constructors and operator overload)
  Vector() noexcept : size_(0), capacity_(0), arr_(nullptr) {}

  Vector(size_type n) : size_(n) {
    arr_ = new value_type[size_];
    for (size_t i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
  }

  Vector(std::initializer_list<value_type> const &items)
      : Vector(items.size()) {
    std::copy(items.begin(), items.end(), arr_);
    // Vector<int> x{1, 2, 3, 4, 5};
    // equal Vector<int> x = {1, 2, 3, 4, 5};
  }

  Vector(const Vector &other) noexcept : Vector(other.size_) {
    std::copy(other.arr_, other.arr_ + other.size_, arr_);
  }

  Vector(Vector &&other) noexcept
      : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~Vector() {
    // remove_vector_();
    if (arr_) {
      delete[] arr_;
    }
    size_ = 0;
    capacity_ = 0;
    arr_ = nullptr;
  }

  Vector &operator=(Vector &&other) {
    ~Vector(); // remove_vector_();
    arr_ = other.arr_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
  }

  // element access
  reference at(size_type pos) {
    if (pos < 0 || pos >= size_) {
      throw out_of_range("Index is out of range");
    }
    return arr_[pos];
  }

  reference operator[](size_type pos) { return arr_[pos]; }

  const_reference front() { return arr_[0]; }

  const_reference back() { return arr_[size_ - 1]; }

  iterator noexcept data() { return arr_; }

  
};
} // namespace s21

#endif // S21_VECTOR_H_
