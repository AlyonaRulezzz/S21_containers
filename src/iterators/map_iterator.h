#ifndef S21_MAP_ITERATOR_H_
#define S21_MAP_ITERATOR_H_

#include <initializer_list>
#include <iostream>
#include <map>
#include <stdexcept>

#include "../s21_tree.h"
#include "tree_iterator.h"
#include "../s21_map.h"

using std::out_of_range;

namespace s21 {
template <typename Key, typename T>
class MapIterator : public TreeIterator<Key, T> {
 public:
 // iterator's operator
  std::pair<Key, T>& operator*() { return this->iter->values; }

  // iterator's constructor
  MapIterator() : TreeIterator<Key, T>() {}

  MapIterator(tree_el_<Key, T>* cur_iter) : TreeIterator<Key, T>(cur_iter) {}


};
}  // namespace s21

#endif  // S21_MAP_ITERATOR_H_