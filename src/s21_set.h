#ifndef S21_SET_H_
#define S21_SET_H_

#include "s21_tree.h"
#include "iterators/tree_iterator.h"
#include "iterators/set_iterator.h"

#include <initializer_list>
#include <stdexcept>
#include <iostream>

#include <vector>
using std::out_of_range;

namespace s21 {
template <typename Key, typename T = int>
class Set : public Tree<Key, T> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<Key, T>;
  using size_type = size_t;

//  Set Member functions
Set() : Tree<Key, T>() {}

// Set(std::initializer_list<value_type> const &items) : Tree<Key, T>(items){}
Set(std::initializer_list<Key> const& items) {
  this->root_ = nullptr;
  this->end_ = nullptr;
  //  it's STD INIT LIST begin & end
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert_tree(*i);
  }
}

Set(const Set &other) {
  *this = other;
}

Set& operator=(const Set &other) {
    this->clear();
    auto e = other.end(); --e; auto i = other.end();
    do {
      ++i;
      this->insert_tree(*i);
    }
    while (i != e);
      return *this;
  }

Set(Set &&m) {
  *this = std::move(m);
}

Set<Key, T> &operator=(Set &&m) {
  this->clear();
  this->root_ = m.root_;
  this->end_ = m.end_;

  m.root_ = nullptr;
  m.end_ = nullptr;
  return *this;
}

~Set() {
  clear();
}


// //  element access
// T& at(const Key& key) {
//   if (search(key) == nullptr) {
//     throw std::out_of_range("No elements with such key");
//   }
//   return search(key)->values.second;
// }


//  T& operator[](const Key& key) {
//   if (search(key) == nullptr) {
//     return (*(insert({key, T()}).first)).second;
//   } else {
//     return search(key)->values.second;
//   }
// }


//  iterators
SetIterator<Key, T> begin() const noexcept {
  SetIterator<Key, T> iterator(this->end_->right);
  return iterator;
}

SetIterator<Key, T> end() const noexcept{
  SetIterator<Key, T> iterator(this->end_);
  return iterator;
}


// capacity
size_type max_size() const noexcept {
  std::allocator<std::pair<Key, T>> Alloc;
  return Alloc.max_size() / 8 * 5 + 1;
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

    if (pos.iter) {
      delete pos.iter;
    }

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


std::pair<iterator, bool> insert(const Key &value) {
  bool insertion = false;
  if (search(value) == nullptr) {
    this->insert_tree(value);
    insertion = true;
  }
  return std::make_pair(iterator(search(value)), insertion);
}


void swap(Set& other) {
  // Map<Key, T> tmp = *this;
  //   std::cout << "\n" << "tmp.size()=" << (*tmp).size() << "\n\n";
  // *this = other;
  //   std::cout << "\n" << "tmp.size()=" << (*tmp).size() << "\n\n";
  // other = *tmp;

  std::swap(this->root_, other.root_);
  std::swap(this->end_, other.end_);
}



void merge(Set& other) {
  auto e = other.end(); --e; auto i = other.end();
    ++i;
  do {
    if ((insert(*i)).second == true) {
      other.erase(i);
      i = other.begin();
    } else {
      ++i;
    }
  }
  while (i != e);

  if ((insert(*i)).second == true) {
    other.erase(i);
  }
}



//  lookup
iterator find(const Key& key) {
  return iterator(this->search_tree(this->root_, key));
}


bool contains(const Key& key) {
  return this->contains_tree(this->root_, key);
}


// // bonus
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


tree_el_<Key, T>*  search_multiset(const Key& key) {
  return this->search_tree_multiset(this->root_, key);
}

Key upper_bound_multiset(const Key& key) {
  return this->upper_bound_tree_multiset(this->root_, key);
}


};
}  // namespace s21

#endif  // S21_SET_H_