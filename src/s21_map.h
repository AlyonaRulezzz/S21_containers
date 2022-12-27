#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "s21_tree.h"
#include "iterators/tree_iterator.h"
#include "iterators/map_iterator.h"

#include <initializer_list>
#include <stdexcept>
#include <iostream>

#include <vector>
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

Map(const Map &other) {
  *this = other;
}

Map& operator=(const Map &other) {
    this->clear();
    auto e = other.end(); --e; auto i = other.end();
    do {
      ++i;
      this->insert_tree(*i);
    }
    while (i != e);
      return *this;
  }

Map(Map &&m) {
  *this = std::move(m);
}

Map<Key, T> &operator=(Map &&m) {
  this->clear();
  this->root_ = m.root_;
  this->end_ = m.end_;

  m.root_ = nullptr;
  m.end_ = nullptr;
  return *this;
}

~Map() {
  clear();
}


//  element access
T& at(const Key& key) {
  if (search(key) == nullptr) {
    throw std::out_of_range("No elements with such key");
  }
  return search(key)->values.second;
}


T& operator[](const Key& key) {
  T* element_value = nullptr;
  int count = 0;
  // for (auto i = begin(); i != end(); ++i) {
  auto e = end(); --e; auto i = end();
  do {
    ++i;
    if ((*i).first == key) {
      element_value = &((*i).second);
      count++;
      break;
    }
  }
  while (i != e);
  if (count == 0) {
    element_value = &(*(insert({key, T()}).first)).second;
  }
  return *element_value;
}


//  iterators
MapIterator<Key, T> begin() const noexcept {
  MapIterator<Key, T> iterator(this->end_->right);
  return iterator;
}

MapIterator<Key, T> end() const noexcept{
  MapIterator<Key, T> iterator(this->end_);
  return iterator;
}


// capacity
size_type max_size() const noexcept {
  std::allocator<std::pair<Key, T>> Alloc;
  return Alloc.max_size() / 9 * 5;
}


//  modifiers
void erase(iterator pos) {
  if (this->size() > 1) {
    auto itb = ++begin();  //  ok
    auto ite = ----end();  //  ok
    auto e = --end();
    if (pos.iter == this->root_) {
      if (this->root_->left) {
        if (this->root_->right) {
          this->insert_tree(this->root_->left, this->root_->right);
        }
        this->root_ = this->root_->left;
      } else {
        this->root_ = this->root_->right;
      }
      this->root_->parent = nullptr;
      this->root_->color = Black;

      if (pos == begin()) {
        this->end_->right = itb.iter;
      }
      if (pos == e/* --end() */) {
        this->end_->left = ite.iter;
      }

    } else {
      if (pos == begin()) {
        this->end_->right = itb.iter;
      }
      if (pos == e/* --end() */) {
        this->end_->left = ite.iter;
      }
        if (pos.iter->parent->left && pos.iter->parent->left == pos.iter) {
          pos.iter->parent->left = nullptr;
        }
        if (pos.iter->parent->right && pos.iter->parent->right == pos.iter) {
          pos.iter->parent->right = nullptr;
        }
      if (pos.iter->left) {
        this->insert_tree(this->root_, pos.iter->left);
      }
      if (pos.iter->right) {
        this->insert_tree(this->root_, pos.iter->right);
      }
    }

    // if (pos.iter) {
      delete pos.iter;
    // }

    pos.iter = nullptr;

  } else if (this->size() == 1) {
    delete this->root_;
    this->root_ = nullptr;
    delete this->end_;
    this->end_ = nullptr;
  }

}

void clear() {
  if (!this->empty()) {
    if (this->size() > 1) {    
      auto i = begin();
      auto e = end(); --e;
      do {
        i = begin();
        erase(i);
      }
      while (begin() != e);
    }
    delete this->root_;
    delete this->end_;
    this->root_ = nullptr;
    this->end_ = nullptr;
  } 

}

std::pair<iterator, bool> insert(const value_type &value) {
  bool insertion = false;
  iterator insert_iterat = nullptr;
  if (!this->empty()) {  
    // for (auto i = begin(); i != end(); ++i) {
    auto e = end(); --e; auto i = end();
    do {
      ++i;
      if ((*i).first == value.first) {
        insert_iterat = i;
        break;
      }
    }
    while (i != e);
  }
  if (insert_iterat == nullptr) {
    this->insert_tree(value);
    insertion = true;
    // for (auto i = begin(); i != end(); ++i) {
    auto e = end(); --e; auto i = end();
    do {
      ++i;
      if ((*i).first == value.first) {
        insert_iterat = i;
        break;
      }
    }
    while (i != e);
  }
  return std::make_pair(insert_iterat, insertion);
}

std::pair<iterator, bool> insert(const Key& key, const T& obj) {
  std::pair<Key, T> value = {key, obj};
  return insert(value);
}

std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
  std::pair<Key, T> value = {key, obj};
  bool insertion = false;
  iterator insert_iterat = nullptr;
  if (!this->empty()) {  
    // for (auto i = begin(); i != end(); ++i) {
    auto e = end(); --e; auto i = end();
    do {
      ++i;
        if ((*i).first == value.first) {
          (*i).second = value.second;
          insert_iterat = i;
          break;
        }
      }
    while (i != e);
  }
  if (insert_iterat == nullptr) {
    this->insert_tree(value);
    insertion = true;
    // for (auto i = begin(); i != end(); ++i) {
    auto e = end(); --e; auto i = end();
    do {
      ++i;
      if ((*i).first == value.first) {
        insert_iterat = i;
        break;
      }
    }
    while (i != e);
  }
  return std::make_pair(insert_iterat, insertion);
}



void swap(Map& other) {
  // Map<Key, T> tmp = *this;
  //   std::cout << "\n" << "tmp.size()=" << (*tmp).size() << "\n\n";
  // *this = other;
  //   std::cout << "\n" << "tmp.size()=" << (*tmp).size() << "\n\n";
  // other = *tmp;

  std::swap(this->root_, other.root_);
  std::swap(this->end_, other.end_);
}



void merge(Map& other) {
  auto e = other.end(); --e; auto i = other.end();
    ++i;
  do {
    if ((insert((*i).first, (*i).second)).second == true) {
      other.erase(i);
      i = other.begin();
    } else {
      ++i;
    }
  }
  while (i != e);

  if ((insert((*i).first, (*i).second)).second == true) {
    other.erase(i);
  }
}



//  lookup
bool contains(const Key& key) {
  return this->contains_tree(this->root_, key);
}


// bonus
template <typename... Args>
std::vector<std::pair<iterator,bool>> emplace(Args&&... args) {
  std::vector<std::pair<iterator, bool>> out;
  for (auto &i:{args...}) {
    out.push_back(insert(i));
  }
  return out;
}


// dop
tree_el_<Key, T>*  search(const Key& key) {
  return this->search_tree(this->root_, key);
}



};
}  // namespace s21

#endif  // S21_MAP_H_