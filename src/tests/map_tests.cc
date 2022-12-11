#include <gtest/gtest.h>

#include <map>

#include "../s21_map.h"
#include "../iterators/map_iterator.h"

// TEST(Constructor, Default) {
//   s21::Map<std::string, int> s;
//   std::map<std::string, int> b;

//   EXPECT_EQ(s.size(), b.size());
//   EXPECT_EQ(s.empty(), b.empty());
// }

// TEST(Map_iterator, operator_dereferencing) {
//   // s21::Map<std::string, int> s = {
//   //     {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
//   //     {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
//   // ;
//   // std::map<std::string, int> b = {
//   //     {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
//   //     {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
//   // ;
//   // auto x = s.begin();
//   // x++;
//   // EXPECT_EQ(*++b.begin(), *x);
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

  std::map<int, int> m2 = {
      {10, 1},   {20, 2}, {30, 3}, {40, 4},
      {50, 5}, {60, 6},  {70, 7}};
    // auto iter1 = m1.end();
    auto iter2 = m2.end();
    ----iter2;
    m2.insert({80, 8});
//     // v1.insert(iter1, 11);
//     v2.insert(iter2, 11);

//     for (size_t i = 0; i < v2.size(); ++i) {
//       EXPECT_EQ(v2.at(i), v2.at(i));
//       std::cout << v2.at(i) << std::endl;
//   }

//     iter1 = v1.begin();
//     iter2 = v2.begin();
//     // v1.insert(iter1 + 5, 11);
//     v2.insert(iter2 + 5, 1001);

//   for (size_t i = 0; i < v2.size(); ++i) {
//     EXPECT_EQ(v2.at(i), v2.at(i));
//     std::cout << v2.at(i) << std::endl;
//   }

//   std::cout << '\n' << std::endl;
  for (auto iter = m2.begin(); iter != m2.end(); ++iter) {
    // EXPECT_EQ(m1.at(i), m2.at(i));
  std::cout << iter->first << ' ' << iter->second << std::endl;
  }
return 0;
}
