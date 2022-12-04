#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <tree.h>

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
Map() {}

Map(std::initializer_list<value_type> const &items) {
  
}



};
}  // namespace s21

#endif  // S21_MAP_H_