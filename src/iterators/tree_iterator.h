#ifndef S21_TREE_ITERATOR_H_
#define S21_TREE_ITERATOR_H_

#include "../s21_tree.h"

#include <initializer_list>
#include <stdexcept>
#include <iostream>

using std::out_of_range;

namespace s21 {

template <typename Key, typename T>
class tree_el_;

template <typename Key, typename T>
class TreeIterator {
 public:
  


tree_el_<Key, T> *iter;

};
}  // namespace s21

#endif  // S21_TREE_ITERATOR_H_