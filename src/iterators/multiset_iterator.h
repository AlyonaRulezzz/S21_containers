#ifndef S21_MULTISET_ITERATOR_H_
#define S21_MULTISET_ITERATOR_H_

#include <initializer_list>
#include <iostream>
#include <set>
#include <stdexcept>
#include "../s21_tree.h"
#include "tree_iterator.h"
#include "../s21_multiset.h"

using std::out_of_range;

namespace s21 {
template <typename Key, typename T = int>
class MultisetIterator : public TreeIterator<Key, T> {
 public:
 // iterator's operator
  Key& operator*() { return this->iter->values.first; }

  // iterator's constructor
  MultisetIterator() : TreeIterator<Key, T>() {}

  MultisetIterator(tree_el_<Key, T>* cur_iter) : TreeIterator<Key, T>(cur_iter) {}


};
}  // namespace s21

#endif  // S21_MULTISET_ITERATOR_H_