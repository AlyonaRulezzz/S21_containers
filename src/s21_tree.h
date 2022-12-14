#ifndef S21_TREE_H_
#define S21_TREE_H_

#include <iostream>

#include "iterators/tree_iterator.h"

namespace s21 {
// declaration
template <typename Key, typename T>
class TreeIterator;

// tree element
enum TreeColor { Black, Red };
template <typename Key, typename T>
class tree_el_ {
 public:
  std::pair<Key, T> values;
  TreeColor color;
  tree_el_* parent;
  tree_el_* left;
  tree_el_* right;

  // tree_el_() : tree_el_(Key(), T()){};
  tree_el_(std::pair<Key, T> val, TreeColor c, tree_el_<Key, T>* p, tree_el_<Key, T>* l, tree_el_<Key, T>* r) :
          values(val), color(c), parent(p), left(l), right(r) {};
};

// Tree
template <typename Key, typename T>
class Tree {
protected:
    tree_el_<Key, T>* root_;
public:
  using size_type = size_t;
  using iterator = TreeIterator<Key, T>;
  // void print();
  // constructor
  Tree() : root_(nullptr) {
    // root_ = nullptr;
  }

  //  tree capacity
  bool empty()  const noexcept {
    return size() == 0;
  }

  size_type size()  const noexcept {
    auto size = counter(root_);
    return size;
  }

  //  dop function
  int counter(tree_el_<Key, T> *cur_el) const {
    if (cur_el == nullptr) {
      return 0;
    }
    return 1 + counter(cur_el->left) + counter(cur_el->right);
  }

//  tree balancing & insert
void insert(tree_el_<Key, T>* root_, tree_el_<Key, T>* new_node) {
  if (new_node->values.first < root_->values.first) {
      if (root_->left == nullptr) {
        root_->left = new_node;
        new_node->parent = root_;
      } else {
        insert(root_->left, new_node);
      }
  } else if (new_node->values.first > root_->values.first) {
      if (root_->right == nullptr) {
        root_->right = new_node;
        new_node->parent = root_;
      } else {
        insert(root_->right, new_node);
      }
  }
  balance(new_node);
}

void insert(const std::pair<Key, T> val) {
  tree_el_<Key, T>* new_node = new tree_el_<Key, T>(val, Red, nullptr, nullptr, nullptr);
  if (empty()) {
    root_ = new_node;
  } else {
    insert(root_, new_node);
  }
  root_->color = Black;
}

void balance(tree_el_<Key, T>* new_node) {
  if (new_node->parent != nullptr) {
    if (new_node->color == Red && 
        new_node == new_node->parent->right &&
        ((new_node->parent->left == nullptr) || (new_node->parent->left->color == Black))) {
          left_turn(new_node->parent);
    }
    
    else if (new_node->parent->parent != nullptr) {
      if (new_node->color == Red && new_node->parent->color == Red &&
          new_node == new_node->parent->left &&
          new_node->parent == new_node->parent->parent->left) {
        right_turn(new_node->parent->parent);
      }
    }

    if (new_node->parent->left && new_node->parent->right && new_node->parent->color == Black) {
      if (new_node->parent->left->color == Red && new_node->parent->right->color == Red) {
        new_node->parent->color == Red;
        new_node->parent->left->color == Black;
        new_node->parent->right->color == Black;
      }
    }

    balance(new_node->parent);
  }
}

void left_turn(tree_el_<Key, T>* node, tree_el_<Key, T>* parent_node) {
  tree_el_<Key, T>* tmp = parent_node->right;
  parent_node->right = tmp->left;
  node->color = Black;
  parent_node->color = Red;
}

//  print tree by russianblogs
void print() const noexcept {
	if (root_ == NULL)
		std::cout << "\nempty RBtree\n" << std::endl;
	else
		print(root_);
}
private:
void print(tree_el_<Key, T>* node)const {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		std::cout << "\n" << node->values.first << "(" << node->color << ") is a root" << std::endl;
	else if(node->parent->left==node)
	{
		std::cout << node->values.first << "(" << node->color << ") is "<<node->parent->values.first<<"'s "<<"left child" << std::endl;
	}
	else
	{
		std::cout << node->values.first << "(" << node->color << ") is " << node->parent->values.first << "'s " << "right child" << std::endl;
	}
	print(node->left);
	print(node->right);
}



};
}  // namespace s21

#endif  // S21_TREE_H_