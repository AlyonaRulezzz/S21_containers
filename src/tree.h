#ifndef S21_TREE_H_
#define S21_TREE_H_

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
  using iterator = MainIterator<Key, T>;

  Tree() : head_(nullptr), begin_(nullptr), end_(nullptr) {}

protected:
    tree_element_<Key, T> *head_, *begin_, *end_;
};



}  // namespace s21

#endif  // S21_TREE_H_