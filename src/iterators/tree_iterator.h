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
  tree_el_<Key, T>* iter;

  // constructor
  TreeIterator() : iter(nullptr) {}
  TreeIterator(tree_el_<Key, T>* cur_iter) : iter(cur_iter) {}

  // iterator's operators
  bool operator==(const TreeIterator<Key, T> &other_iter) {
    return iter == other_iter.iter;
  }

  bool operator!=(const TreeIterator<Key, T> &other_iter) {
    return iter != other_iter.iter;
  }

  TreeIterator<Key, T> operator++() {
    if (iter->right) {
      if (iter->right->left) {
        iter = iter->right->left;
      } else {
        iter = iter->right;
      }
    } else if (iter->parent && iter == iter->parent->left) {
      iter = iter->parent;
    } else if (iter->parent && iter->paren->parent && iter == iter->parent->right) {
      iter = iter->paren->parent;
    } 
    // else if (iter == root_) {  // ??????
      
    // }
    return *this;
  }

  TreeIterator<Key, T> operator--() {
    if (iter->left) {
      if (iter->left->right) {
        iter = iter->left->right;
      } else {
        iter = iter->left;
      }
    } else if (iter->parent && iter == iter->parent->right) {
      iter = iter->parent;
    } else if (iter->parent && iter->paren->parent && iter == iter->parent->left) {
      iter = iter->paren->parent;
    } 
    // else if (iter == root_) {  // ??????
      
    // }
    return *this;
  }

};
}  // namespace s21

#endif  // S21_TREE_ITERATOR_H_