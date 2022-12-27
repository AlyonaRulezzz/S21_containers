#ifndef S21_TREE_H_
#define S21_TREE_H_

#include <iostream>

#include "iterators/tree_iterator.h"

namespace s21 {
// declaration
template <typename Key, typename T>
class TreeIterator;

template <typename Key, typename T>
class tree_el_;


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

  tree_el_() : tree_el_(Key(), T()){};
  tree_el_(std::pair<Key, T> val, TreeColor c,
  tree_el_<Key, T>* p, tree_el_<Key, T>* l, tree_el_<Key, T>* r) :
          values(val), color(c), parent(p), left(l), right(r) {};
};

// Tree
template <typename Key, typename T>
class Tree {
protected:
    tree_el_<Key, T>* root_;
    tree_el_<Key, T>* end_;

public:
  using size_type = size_t;
  using iterator = TreeIterator<Key, T>;

  // constructor
  Tree() : root_(nullptr), end_(nullptr) {
  }

  Tree(std::initializer_list<std::pair<const Key, T>> const& items) {
    root_ = nullptr;
    end_ = nullptr;
    //  it's STD INIT LIST begin & end
    for (auto i = items.begin(); i != items.end(); ++i) {
      insert_tree(*i);
    }
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


//  tree balancing & insert_tree
void insert_tree(tree_el_<Key, T>* root_, tree_el_<Key, T>* new_node) {
  if (new_node->values.first < root_->values.first) {
    if (root_->left == nullptr) {
      root_->left = new_node;
      new_node->parent = root_;
    } else {
      insert_tree(root_->left, new_node);
    }
  } else if (new_node->values.first > root_->values.first) {
    if (root_->right == nullptr) {
      root_->right = new_node;
      new_node->parent = root_;
    } else {
      insert_tree(root_->right, new_node);
    }
  }
  balance(new_node);
}

void insert_tree(const std::pair<Key, T> val) {
  tree_el_<Key, T>* new_node = new tree_el_<Key, T>(val, Red, nullptr, nullptr, nullptr);

  if (empty()) {
    root_ = new_node;
    if (end_ == nullptr) {
      end_ = new tree_el_<Key, T>(val, Red, nullptr, new_node, new_node);
    }
  } else {
    insert_tree(root_, new_node);

    if (new_node->values.first > end_->left->values.first) {
      end_->left = new_node;
    }
    if (new_node->values.first < end_->right->values.first) {
      end_->right = new_node;
    }

  }
  root_->color = Black;
}

void balance(tree_el_<Key, T>* new_node) {
  if (new_node) {  
    if (new_node->parent != nullptr) {
      if (new_node->color == Red && 
          new_node == new_node->parent->right &&
          ((new_node->parent->left == nullptr) || (new_node->parent->left->color == Black))) {
            left_turn(root_, new_node->parent);
      }
      
      else if (new_node->parent->parent != nullptr) {
        if (new_node->color == Red && new_node->parent->color == Red &&
            new_node == new_node->parent->left &&
            new_node->parent == new_node->parent->parent->left) {
          right_turn(root_, new_node->parent->parent);
        }
      }

      if (new_node->parent != nullptr) {
        if (new_node->parent->left && new_node->parent->right && (new_node->parent->color == Black)) {
          if ((new_node->parent->left->color == Red) && (new_node->parent->right->color == Red)) {
            new_node->parent->color = Red;
            new_node->parent->left->color = Black;
            new_node->parent->right->color = Black;
          }
        }
      }

      balance(new_node->parent);
    }
  }
}

void left_turn(tree_el_<Key, T>* &root_, tree_el_<Key, T>* x) {
  x->color = Red;
  x->right->color = Black;

  tree_el_<Key, T>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root_ = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;

  // if (root_->parent != nullptr) {
  //   root_ = root_->parent;
  // }
}

void right_turn(tree_el_<Key, T>* &root_, tree_el_<Key, T>* y) {
  y->color = Red;
  y->left->color = Black;

	tree_el_<Key, T>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root_ = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;

  // if (root_->parent != nullptr) {
  //   root_ = root_->parent;
  // }
}

//  print tree by russianblogs
void print() const noexcept {
	if (root_ == NULL)
		std::cout << "\nempty RBtree\n" << std::endl;
	else
		print(root_);

// std::cout << end_->left->values.first << std::endl;
// std::cout << end_->right->values.first << std::endl;

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

public:
tree_el_<Key, T>*  search_tree(tree_el_<Key, T>* node, const Key& key) {
  while (node != NULL) {

    if (node->values.first == key) {
      return node;

    } else if (key < node->values.first && node->left) {
      node = node->left;

    } else if (key > node->values.first && node->right) {
      node = node->right;

    } else {
      break;
    }

  }
  return nullptr;
}


bool contains_tree(tree_el_<Key, T>* node, const Key& key) {
  return (search_tree(root_, key)) ? true : false;
}



};
}  // namespace s21

#endif  // S21_TREE_H_