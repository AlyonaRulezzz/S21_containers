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
//     for (auto it = other.begin(); it != other.end(); ++it) insert_tree(*it);
//     return *this;
// }

// Map(const Map &other) : Tree<Key, T>(other) {}
  Map(const Map &other) {
    *this = other;
  }


//

Map& operator=(const Map &other) {
    this->clear();  //NEED TO FIX THIS (FIX ERASE)
    // std::cout << "\n" << "other.size()=" << other.size() << "\n";
    // for (auto i = other.begin(); i != other.end(); ++i) 
    auto e = other.end(); --e; auto i = other.end();
    do {
      ++i;
      this->insert_tree(*i);
    }
    while (i != e);
      return *this;
  }

// Map(const Map &other): Tree<Key, T>(other) {
//   *this = other;
// }

Map(Map &&m) {
  *this = std::move(m);
}

Map<Key, T> &operator=(Map &&m) {
  this->clear();  //  Does clear really need hear???   NEED TO FIX THIS (FIX ERASE)
  this->root_ = m.root_;
  this->end_ = m.end_;

  m.root_ = nullptr;
  m.end_ = nullptr;
  return *this;
}
//

~Map() {
  clear();

}


// capacity
size_type max_size() const noexcept {
  std::allocator<std::pair<Key, T>> Alloc;
  // std::allocator<value_type> Alloc;
  return Alloc.max_size() / 9 * 5;
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

  //  modifiers
  // void erase(iterator pos) {
  //   Tree<Key, T>::erase(pos);
  // }
// void erase(iterator pos) {
//   auto itb = ++begin();  //  ok
//   auto ite = ----end();  //  ok
//   if (this->size() > 1) {
//     if (pos.iter == this->root_) {
//       if (this->root_->left) {
//         // this->root_->right->color = Red;  /////////////////////// ???????????
//         this->insert_tree(this->root_->left, this->root_->right);
//         this->root_ = this->root_->left;
//       } else {
//         this->root_ = this->root_->right;
//       }
//       this->root_->parent = nullptr;
//       this->root_->color = Black;
//     } else {
//       if (pos == begin()) {
//         this->end_->right = itb.iter;
//       }
//       if (pos == --end()) {
//         this->end_->left = ite.iter;
//       }

//       if (pos.iter->parent->left == pos.iter) {
//         pos.iter->parent->left = nullptr;
//       }
//       if (pos.iter->parent->right == pos.iter) {
//         pos.iter->parent->right = nullptr;
//       }

//       if (pos.iter->left) {
//         this->insert_tree(this->root_, pos.iter->left);
//       }
//       if (pos.iter->right) {
//         this->insert_tree(this->root_, pos.iter->right);
//       }
//     }
//   }

//   if (pos.iter) {
//     delete pos.iter;
//   }
//   pos.iter = nullptr;
// }



void erase(iterator pos) {
  if (this->size() > 1) {
    auto itb = ++begin();  //  ok
    auto ite = ----end();  //  ok
    auto e = --end(); ////////
    if (pos.iter == this->root_) {
      if (this->root_->left) {
        // this->root_->right->color = Red;  /////////////////////// ???????????
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
    // this->print();
      // if (pos.iter->parent) {
        if (pos.iter->parent->left && pos.iter->parent->left == pos.iter) {
          pos.iter->parent->left = nullptr;
        }
        if (pos.iter->parent->right && pos.iter->parent->right == pos.iter) {
          pos.iter->parent->right = nullptr;
        }
      // }

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
    // this->print();

  } else if (this->size() == 1) {
    delete this->root_;
    this->root_ = nullptr;
    delete this->end_;
    this->end_ = nullptr;
  }
// this->print();
// std::cout << this->size();

}

void clear() {
  if (!this->empty()) {
    if (this->size() > 1) {    
      auto i = begin();  //////
      auto e = end(); --e;  //////

      // for (auto i = begin(); i != end(); ++i) {
      // auto e = end(); ----e; auto i = end(); ++i;
      // auto e = end(); --e; auto i = end();
      do {        
        // std::cout << "\n" <<std::endl;
        // ++i;
        i = begin();  //////
        // std::cout << (*i).first << "\n" <<std::endl;
        // std::cout << "before erase";
        // this->print(); 
        // std::cout << "\n" <<std::endl;
        erase(i);
        // std::cout << this->size();
        // this->print();
        // std::cout << "after erase";
        // this->print();
        // std::cout << "\n" <<std::endl;
        // std::cout << "-------------------------\n";
      }
      // while (i != e);
      // while (begin() != nullptr);
      while (begin() != e);
        // std::cout <<"\n" << "(*begin()).first=" << (begin()).iter << "\n" <<std::endl;
        // std::cout << "(*e).first=" << (e).iter << "\n" <<std::endl;
    }
    // if (this->size() > 1) {    
    delete this->root_;
    delete this->end_;
    this->root_ = nullptr;
    this->end_ = nullptr;
        // this->print();
        // std::cout << this->size();
    // }
  } 
  // else if (this->size() == 1) {
    // erase(this->root_);
  // }

    // std::cout << "after erase";
    // this->print();
    // std::cout << "\n" <<std::endl;
    // std::cout << "-------------------------\n";
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

//  element access
// T& at(const Key& key) {  // with for but doesnt work with clean end()
//   static T element_value = T();
//   int count = 0;
//   // auto e = end();
//   for (auto i = begin(); i != end(); ++i) {
//   // for (auto i = begin(); i != e; ++i) {
//   // for (auto i = (++iterator(this->end_)); i != (iterator(this->end_)); ++i) {
//     // auto ie = end(); 
//     // // i;
//     // auto i = begin(); ++++++++++++++++++++i;
//   // std::cout << (iterator(this->end_)).iter  << std::endl;
//   // std::cout << (this->end()).iter  << std::endl;
//   // std::cout << (++++++++++++++++++++this->begin()).iter  << std::endl;
//   //   std::cout << (++iterator(this->end_)).iter  << std::endl;
//   // std::cout << (this->begin()).iter  << std::endl;

//   // std::cout << (*ie).first  << std::endl;
//   // std::cout << (*i).first  << std::endl;
//     if ((*i).first == key) {
//       element_value = (*i).second;
//       count++;
//       break;
//     }
//   }
//   if (count == 0) {
//     throw std::out_of_range("No elements with such key");
//   }
//   return element_value;
// }

T& at(const Key& key) { //   need to fix (add & to the element)
  static T element_value = T();
  int count = 0;
  auto e = end(); --e; auto i = end();
  do {
    ++i;
  // std::cout << (*i).first  << std::endl;
    if ((*i).first == key) {
      element_value = (*i).second;
      count++;
      break;
    }
  }
  while (i != e);
  if (count == 0) {
    throw std::out_of_range("No elements with such key");
  }
  return element_value;
}

T& operator[](const Key& key) { //   need to fix (add & to the element)
  static T element_value = T();
  int count = 0;
  // for (auto i = begin(); i != end(); ++i) {
  auto e = end(); --e; auto i = end();
  do {
    ++i;
    if ((*i).first == key) {
      element_value = (*i).second;
      count++;
      break;
    }
  }
  while (i != e);
  if (count == 0) {
    this->insert_tree({key, T()});
  }

  // i = end();
  // do {
  //   ++i;
  //   std::cout << (*i).first << " " << (*i).second << std::endl;
  //   // std::cout << (*i).second  << std::endl;
  // }
  // while (i != e);
  // this->print();
    // std::cout << (this->begin()).iter->values.second  << std::endl;
    // std::cout << (++this->begin()).iter->values.second  << std::endl;
    // std::cout << (++++this->begin()).iter->values.second  << std::endl;

  return element_value;
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
  // other.print();
  auto e = other.end(); --e; auto i = other.end();
    ++i;
    // auto i = other.begin();
  do {
      // std::cout << "\n" << (*i).first;
    if ((insert((*i).first, (*i).second)).second == true) {
      other.erase(i);  //NEED TO FIX ERASE
      i = other.begin();
      // std::cout << "\n\t" << (*i).first;
    } else {
      ++i;
    }
  }
  while (i != e);

  if ((insert((*i).first, (*i).second)).second == true) {
    other.erase(i);  //NEED TO FIX ERASE
  }
}



//  lookup
bool contains(const Key& key) {
  // for (auto i = begin(); i != end(); ++i) {
  auto e = end(); --e; auto i = end();
  do {
    ++i;
    if ((*i).first == key) {
      return true;
    }
  }
  while (i != e);
  return false;
}

template <typename... Args>
std::vector<std::pair<iterator,bool>> emplace(Args&&... args) {
  std::vector<std::pair<iterator, bool>> out;
  for (auto &i:{args...}) {
    out.push_back(insert(i));
  }
  return out;
}


};
}  // namespace s21

#endif  // S21_MAP_H_