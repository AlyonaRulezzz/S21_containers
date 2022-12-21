#include <gtest/gtest.h>

#include <map>
#include <initializer_list>

#include "../s21_tree.h"

#include "../s21_map.h"
#include "../iterators/map_iterator.h"

// TEST(Constructor, Default) {
//   s21::Map<std::string, int> s;
//   std::map<std::string, int> b;

//   EXPECT_EQ(s.size(), b.size());
//   EXPECT_EQ(s.empty(), b.empty());
// }

// TEST(Map_iterator, operator_dereferencing_initializer_list_plusplus_minusminus_begin_end) {
//   s21::Map<int, std::string> s = {
//       {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
//       {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};

//   std::map<int, std::string> b = {
//       {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
//       {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};

//   auto si = s.begin();
//   auto bi = b.begin();
//   for (; si != s.end() && bi != b.end(); ++si, ++bi) {
//     EXPECT_EQ((*si).first, (*bi).first);
//     EXPECT_EQ((*si).second, (*bi).second);
//   }

//   si = s.end();
//   bi = b.end();
//   ----si;
//   ----bi;
//   EXPECT_EQ((*si).first, (*bi).first);
//   // EXPECT_EQ((*si).second, (*bi).second);  ??????????????? why sega???

//   EXPECT_EQ(s.size(), b.size());
//   EXPECT_EQ(s.empty(), b.empty());
// }

// TEST(MapConstructors, Copy) {
// //   s21::Map<int, std::string> s_tree = {
// //       {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
// //       {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
// //   s21::Map<int, std::string> cp_s_tree = s_tree;

// //   std::map<int, std::string> o_tree = {
// //       {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
// //       {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
// //   std::map<int, std::string> cp_o_tree = o_tree;

// //   auto si = cp_s_tree.begin();
// //   auto oi = cp_o_tree.begin();
// //   for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
// //     EXPECT_EQ((*si).first, (*oi).first);
// //     EXPECT_EQ((*si).second, (*oi).second);
// //   }

// //   EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
// //   EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
// }

// TEST(MapModifiers, Erase) {
//   s21::Map<std::string, int> s_tree = {
//       {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
//       {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

//   std::map<std::string, int> o_tree = {
//       {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
//       {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

//   EXPECT_EQ(s_tree.size(), o_tree.size());
//   EXPECT_EQ(s_tree.empty(), o_tree.empty());

//   auto si = s_tree.begin();
//   auto oi = o_tree.begin();
//   // ++++++++++++++++si;
//   ++++++++++++++++oi;
//   // for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
//     EXPECT_EQ((*si).first, (*oi).first);
//     EXPECT_EQ((*si).second, (*oi).second);
//   // }

//   // auto s_it = s_tree.begin();
//   // auto o_it = o_tree.begin();
//   // ++ ++ ++ ++s_it;
//   // ++ ++ ++ ++o_it;

//   // s_tree.erase(s_it);
//   // o_tree.erase(o_it);

//   // EXPECT_EQ(s_tree.size(), o_tree.size());
//   // EXPECT_EQ(s_tree.empty(), o_tree.empty());

//   // si = s_tree.begin();
//   // oi = o_tree.begin();
//   // for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
//   //   EXPECT_EQ((*si).first, (*oi).first);
//   //   EXPECT_EQ((*si).second, (*oi).second);
//   // }
// }

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }


///////////////////////////////
#include <iostream>

int main() {
  // s21::Map<int, int> m1 = {
  //     {10, 1},   {20, 2}, {30, 3}, {40, 4},
  //     {50, 5}, {60, 6},  {70, 7}};

  s21::Map<std::string, int> m1 = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

std::map<std::string, int> m2 = {
        {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

//   std::map<int, int> m2 = {
//       {10, 1}
// //   };
//       ,   {20, 2}, {30, 3}, {40, 4},
//       {50, 5}, {60, 6},  {70, 7}};
//     // auto iter1 = m1.end();
//     auto iter2 = m2.end();
//     ----iter2;
//     m2.insert({80, 8});
// //     // v1.insert(iter1, 11);
// //     v2.insert(iter2, 11);

// //     for (size_t i = 0; i < v2.size(); ++i) {
// //       EXPECT_EQ(v2.at(i), v2.at(i));
// //       std::cout << v2.at(i) << std::endl;
// //   }

// //     iter1 = v1.begin();
// //     iter2 = v2.begin();
// //     // v1.insert(iter1 + 5, 11);
// //     v2.insert(iter2 + 5, 1001);

// //   for (size_t i = 0; i < v2.size(); ++i) {
// //     EXPECT_EQ(v2.at(i), v2.at(i));
// //     std::cout << v2.at(i) << std::endl;
// //   }

  // for (auto iter1 = m1.begin(); iter1 != m1.end(); ++iter1) {
    auto iter1 = ++++++++++++++++m1.begin();
  std::cout << iter1.iter->values.first << ' ' << iter1.iter->values.second << std::endl;
  // }
  std::cout << '\n' << std::endl;
  for (auto iter2 = m2.begin(); iter2 != m2.end(); ++iter2) {
    // EXPECT_EQ(m1.at(i), m2.at(i));
  std::cout << iter2->first << ' ' << iter2->second << std::endl;
  }

// s21::Tree<int, int> t1;
// t1.print();

// s21::Map<int, int> m1;
// m1.insert({24, 1});
// m1.insert({5, 2});
// m1.insert({1, 2});
// m1.insert({15, 2});
// m1.insert({3, 2});
// m1.insert({8, 2});
// // m1.insert({11, 2});
// m1.print();
// // auto iter1 = --(++++m1.begin());
// auto iter1 = m1.begin();
// auto iter2 = m1.end();

// --iter2;

// std::cout << iter1.iter->values.first << std::endl;
// std::cout << iter2.iter->values.first << std::endl;

// m1.erase(iter1);
// iter1 = m1.begin();
// ++++iter1;
// m1.erase(iter1);
// m1.erase(iter2);

// std::cout << m1.size() << std::endl;

// iter1 = m1.begin();  //  change after erase
// iter2 = m1.end();
// --iter2;
// std::cout << iter1.iter->values.first << std::endl;
// std::cout << iter2.iter->values.first << std::endl;

// m1.print();

// // std::cout << m2.end()._M_node << std::endl;
// // std::cout << m2.end()._M_node->_M_left << std::endl;
// // std::cout << m2.end()._M_node->_M_right << std::endl;
// // std::cout << m2.end()._M_node->_M_parent << std::endl;
// // std::cout << (--m2.end())._M_node << std::endl;
// std::cout << m2.begin()._M_node << std::endl;
// std::cout << (m2.end())._M_node->_M_left << std::endl;

// std::cout << (--m2.end())._M_node << std::endl;
// std::cout << (m2.end())._M_node->_M_right << std::endl;
// // std::cout << (--m2.end())._M_node->_M_parent << std::endl;
// // std::cout << (--m2.end())._M_node->_M_left << std::endl;
// // std::cout << (--m2.end())._M_node->_M_right << std::endl;

// m2.end();

return 0;
}
