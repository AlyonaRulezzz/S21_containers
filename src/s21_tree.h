#ifndef S21_TREE_H_
#define S21_TREE_H_

#include "iterators/tree_iterator.h"

namespace s21 {
// declaration
template <typename Key, typename T>
class TreeIterator;

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







public:
//  print tree
// template<typename Key, typename T>
    void print_tree(tree_el_<Key, T>* current) {
        if (current->left != nullptr) {
            print_tree(current->left);
        }
        if (current != this->end_)
            std::cout << "Value = " << current->values.first << "    adress = " << current <<
            "    adress back = " << current->back << "   from = " << current->back->values.first<< std::endl;
        if (current->right != nullptr) {
            print_tree(current->right);
        }
    }

    // template<typename Key, typename T>
    void print() {
        print_tree(this->head_);
    }



};



}  // namespace s21

#endif  // S21_TREE_H_