#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "s21_tree.h"
#include "iterators/tree_iterator.h"
#include "iterators/map_iterator.h"

#include <initializer_list>
#include <stdexcept>
#include <iostream>

using std::out_of_range;

namespace s21 {
template <typename Key, typename T>
class Map : public Tree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator<Key, T>;
  using size_type = size_t;

//  Map Member functions
Map() : Tree<Key, T>() {}

Map(std::initializer_list<value_type> const &items) : Tree<Key, T>(items){}
// Map &operator=(Map &other) = default;
// Map &operator=(Map &other) {
//     this->clear();
//     for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
//     return *this;
// }

// Map(const Map &other) : Tree<Key, T>(other) {}

//  iterators
MapIterator<Key, T> begin() const noexcept {
  MapIterator<Key, T> iterator(this->end_->right);
  return iterator;
}

MapIterator<Key, T> end() const noexcept{
  MapIterator<Key, T> iterator(this->end_);
  return iterator;
}

  //  modifiers
  // void erase(iterator pos) {
  //   Tree<Key, T>::erase(pos);
  // }
void erase(iterator pos) {
  auto itb = ++begin();
  auto ite = ----end();
  if (this->size() > 1) {
    if (pos.iter == this->root_) {
      if (this->root_->left) {
        // this->root_->right->color = Red;  /////////////////////// ???????????
        this->insert(this->root_->left, this->root_->right);
        this->root_ = this->root_->left;
      } else {
        this->root_ = this->root_->right;
      }
      this->root_->parent = nullptr;
      this->root_->color = Black;
    } else {
      if (pos == begin()) {
        this->end_->right = itb.iter;
      }
      if (pos == --end()) {
        this->end_->left = ite.iter;
      }

      if (pos.iter->parent->left == pos.iter) {
        pos.iter->parent->left = nullptr;
      }
      if (pos.iter->parent->right == pos.iter) {
        pos.iter->parent->right = nullptr;
      }

      if (pos.iter->left) {
        this->insert(this->root_, pos.iter->left);
      }
      if (pos.iter->right) {
        this->insert(this->root_, pos.iter->right);
      }
    }
  }

  delete pos.iter;
  pos.iter = nullptr;
}

  void clear() {
    for (auto it = begin(); it != end(); ++it) {
      erase(it);
    }
    delete this->root_;
    delete this->end_;
    this->root_ = nullptr;
    this->end_ = nullptr;
  }

//  element access
T& at(const Key& key) {
  static T element_value = T();
  int count = 0;
  // auto e = end();
  for (auto i = begin(); i != end(); ++i) {
  // for (auto i = begin(); i != e; ++i) {
  // for (auto i = (++iterator(this->end_)); i != (iterator(this->end_)); ++i) {
    // auto ie = end(); 
    // // i;
    // auto i = begin(); ++++++++++++++++++++i;
  // std::cout << (iterator(this->end_)).iter  << std::endl;
  // std::cout << (this->end()).iter  << std::endl;
  // std::cout << (++++++++++++++++++++this->begin()).iter  << std::endl;
  //   std::cout << (++iterator(this->end_)).iter  << std::endl;
  // std::cout << (this->begin()).iter  << std::endl;

  // std::cout << (*ie).first  << std::endl;
  // std::cout << (*i).first  << std::endl;
    if ((*i).first == key) {
      element_value = (*i).second;
      count++;
      break;
    }
  }
  if (count == 0) {
    throw std::out_of_range("No elements with such key");
  }
  return element_value;
}
///////////
T& operator[](const Key& key) {
  static T element_value = T();
  int count = 0;

  auto e = --end();  //  why exactly end doesnt work????
  for (auto i = begin(); i != e; ++i) {
  // for (auto i = begin(); i != end(); ++i) {
    if ((*i).first == key) {
      element_value = (*i).second;
      count++;
      break;
    }
  }
  if (count == 0) {
    this->insert({key, T()});
  }

  // this->print();
    // std::cout << (this->begin()).iter->values.second  << std::endl;
    // std::cout << (++this->begin()).iter->values.second  << std::endl;
    // std::cout << (++++this->begin()).iter->values.second  << std::endl;

  return element_value;
}

//  lookup
bool contains(const Key& key) {
  // auto e = end();
  for (auto i = begin(); i != end(); ++i) {
  // for (auto i = begin(); i != e; ++i) {
    if ((*i).first == key) {
      return true;
    }
  }
  return false;
}


};
}  // namespace s21

#endif  // S21_MAP_H_