#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include "iterators/vector_iterator.h"
#include <initializer_list>
#include <stdexcept>

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

public:
  // functions (constructors and operator overload)
  Vector() noexcept : size_(0), capacity_(0), arr_(nullptr) {}

  Vector(size_type n) : size_(n) {
    arr_ = new value_type[size_];
    for (size_t i = 0; i < size_; i++) {
      arr_[i] = value_type();
    }
  }

  Vector(std::initializer_list<value_type> const &items) {
    // Vector<int> x{1, 2, 3, 4, 5};
    // equal Vector<int> x = {1, 2, 3, 4, 5};

  }

  
};
} // namespace s21

#endif // S21_VECTOR_H_
