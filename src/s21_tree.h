#ifndef S21_TREE_H_
#define S21_TREE_H_

#include "iterators/tree_iterator.h"

namespace s21 {
// tree element
template <typename Key, typename T>
class tree_el_ {
 public:
  std::pair<Key, T> values;
  tree_el_ *up;
  tree_el_ *left;
  tree_el_ *right;

  tree_el_() : tree_el_(Key(), T()){};
  tree_el_(Key k, T val);
};

// Tree
template <typename Key, typename T>
class Tree {
public:
  using size_type = size_t;
  using iterator = TreeIterator<Key, T>;
  // constructor
  Tree() : head_(nullptr), begin_(nullptr), end_(nullptr) {}

  //  tree capacity
  bool empty()  const noexcept {
    return size() == 0;
  }

  size_type size()  const noexcept {
    auto size = counter(head_);
    return size;
  }

  //  dop function
  int counter(tree_el_<Key, T> *cur_el) const {
    if (cur_el == nullptr) {
      return 0;
    }
    return 1 + counter(cur_el->left) + counter(cur_el->right);
  }


protected:
    tree_el_<Key, T> *head_, *begin_, *end_;
};



}  // namespace s21

#endif  // S21_TREE_H_