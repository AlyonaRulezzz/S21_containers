#ifndef S21_TREE_ITERATOR_H_
#define S21_TREE_ITERATOR_H_

#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "../s21_tree.h"

using std::out_of_range;

namespace s21 {
// declaration
template <typename Key, typename T>
class tree_el_;
template <typename Key, typename T>
class Tree;

template <typename Key, typename T>
class TreeIterator {
 public:
  tree_el_<Key, T> *iter;

  // constructor
  TreeIterator() : iter(nullptr) {}
  TreeIterator(tree_el_<Key, T> *cur_iter) : iter(cur_iter) {}

  // iterator's operators
  bool operator==(const TreeIterator<Key, T> &other_iter) {
    return iter == other_iter.iter;
  }

  bool operator!=(const TreeIterator<Key, T> &other_iter) {
    return iter != other_iter.iter;
  }

  TreeIterator<Key, T> &operator++() { this->iter; }
};
}  // namespace s21

#endif  // S21_TREE_ITERATOR_H_