#include <gtest/gtest.h>

#include <map>
#include <initializer_list>

#include "../s21_tree.h"

#include "../s21_map.h"
#include "../iterators/map_iterator.h"

TEST(Constructor, Default) {
  s21::Map<std::string, int> s;
  std::map<std::string, int> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(Map_iterator, initializer_list_operator_dereferencing_plusplus_minusminus_begin_end) {
  s21::Map<int, std::string> s = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};

  std::map<int, std::string> b = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};

  auto si = s.begin();
  auto bi = b.begin();
  for (; si != s.end() && bi != b.end(); ++si, ++bi) {
    EXPECT_EQ((*si).first, (*bi).first);
    EXPECT_EQ((*si).second, (*bi).second);
  }

  si = s.end();
  bi = b.end();
  ----si;
  ----bi;
  EXPECT_EQ((*si).first, (*bi).first);
  EXPECT_EQ((*si).second, (*bi).second);

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MapConstructors, Copy) {
  s21::Map<int, std::string> s_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  // s21::Map<int, std::string>& cp_s_tree = s_tree;
  s21::Map<int, std::string>& cp_s_tree(s_tree);

  std::map<int, std::string> o_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  std::map<int, std::string> cp_o_tree = o_tree;

  auto si = cp_s_tree.begin();
  auto oi = cp_o_tree.begin();
  for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
  EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
}

TEST(MapConstructors, Move) {
  s21::Map<int, std::string> s_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  s21::Map<int, std::string> mv_s_tree = std::move(s_tree);

  std::map<int, std::string> o_tree = {
      {10, "ten"},   {20, "twenty"}, {30, "thirty"}, {40, "fourty"},
      {50, "fifty"}, {60, "sixty"},  {70, "seventy"}};
  std::map<int, std::string> mv_o_tree = std::move(o_tree);

  auto si = mv_s_tree.begin();
  auto oi = mv_o_tree.begin();
  for (; si != mv_s_tree.end() && oi != mv_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(mv_s_tree.size(), mv_o_tree.size());
  EXPECT_EQ(mv_s_tree.empty(), mv_o_tree.empty());

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MapConstructors, Operator_equal) {
  s21::Map<int, int> m1 = {
      {10, 1},   {20, 2}, {30, 3}, {40, 4},
      {50, 5}, {60, 6},  {70, 7}};

  s21::Map<int, int>& m2 = m1;

  auto e = m1.end(); --e; auto i = m1.end();
  do {
    ++i;
    EXPECT_EQ((*i).first, (*i).first);
    EXPECT_EQ((*i).second, (*i).second);
  }
  while (i != e);

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(MapModifiers, Erase) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  // ++++++++++++++++si;
  // ++++++++++++++++oi;
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  auto s_it = s_tree.begin();
  auto o_it = o_tree.begin();
  ++ ++ ++ ++s_it;
  ++ ++ ++ ++o_it;

  s_tree.erase(s_it);
  o_tree.erase(o_it);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  si = s_tree.begin();
  oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(MapElementAccess, At) {
  s21::Map<std::string, int> m1 = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(0, m1.at("zero"));
  EXPECT_EQ(5, m1.at("five"));
  EXPECT_EQ(8, m1.at("eight"));
  EXPECT_EQ(9, m1.at("nine"));

  EXPECT_ANY_THROW(m1.at("SSD"));

}

TEST(MapElementAccess, Brackets) {
  s21::Map<std::string, std::string> s_tree = {
      {"CPU", "Intel"}, {"GPU", "Nvidia"}, {"RAM", "64GB"}};

  std::map<std::string, std::string> o_tree = {
      {"CPU", "Intel"}, {"GPU", "Nvidia"}, {"RAM", "64GB"}};

  EXPECT_EQ(s_tree["CPU"], o_tree["CPU"]);
  EXPECT_EQ(s_tree["GPU"], o_tree["GPU"]);
  EXPECT_EQ(s_tree["RAM"], o_tree["RAM"]);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  s_tree["SSD"] //   need to fix (add & to the element)
  ;
  // = "yyyyy";
  EXPECT_EQ(s_tree["SSD"], o_tree["SSD"]);
}

TEST(MapLookup, Contains) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

TEST(MapModifiers, InsertPair) {
  s21::Map<std::string, int> s_tree
  // ;
   = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree 
  // ;
  = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  // s_tree.clear();
  // o_tree.clear();

  auto s_pr = s_tree.insert({"one", 0});
  auto o_pr = o_tree.insert({"one", 0});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"ten", 10});
  o_pr = o_tree.insert({"ten", 10});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"twelve", 20});
  o_pr = o_tree.insert({"twelve", 20});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert({"thirty", 30});
  o_pr = o_tree.insert({"thirty", 30});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MapModifiers, InsertObjects) {
  s21::Map<std::string, int> s_tree;
  std::map<std::string, int> o_tree;

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  // s_tree.clear();
  // o_tree.clear();

  auto s_pr = s_tree.insert("ten", 10);
  auto o_pr = o_tree.insert({"ten", 10});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert("twelve", 20);
  o_pr = o_tree.insert({"twelve", 20});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert("thirty", 30);
  o_pr = o_tree.insert({"thirty", 30});
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MapModifiers, InsertOrAssign) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto s_pr = s_tree.insert_or_assign("ten", 10);
  auto o_pr = o_tree.insert_or_assign("ten", 10);
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert_or_assign("zero", -1);
  o_pr = o_tree.insert_or_assign("zero", -1);
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  s_pr = s_tree.insert_or_assign("seven", 777);
  o_pr = o_tree.insert_or_assign("seven", 777);
  EXPECT_EQ((*(s_pr.first)).first, (*(o_pr.first)).first);
  EXPECT_EQ((*(s_pr.first)).second, (*(o_pr.first)).second);
  EXPECT_EQ(s_pr.second, o_pr.second);

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(FixErase, Swap) {
  s21::Map<std::string, int> f_s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  s21::Map<std::string, int> s_s_tree = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  std::map<std::string, int> f_o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> s_o_tree = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }

  f_o_tree.swap(s_o_tree);
  f_s_tree.swap(s_s_tree);

  // EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  // EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  // EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  // EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  // si = f_s_tree.begin();
  // oi = f_o_tree.begin();
  // for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
  //   EXPECT_EQ((*si).first, (*oi).first);
  //   EXPECT_EQ((*si).second, (*oi).second);
  // }
  // si = s_s_tree.begin();
  // oi = s_o_tree.begin();
  // for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
  //   EXPECT_EQ((*si).first, (*oi).first);
  //   EXPECT_EQ((*si).second, (*oi).second);
  // }
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  // s21::Map<std::string, int> s_tree
  // // ;
  //  = {
  //     {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
  //     {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  // auto e = s_tree.end(); --e; auto i = s_tree.end();
  // // do {
  //   // ++i;
  //   std::cout << (*e).first <<std::endl;
  //   s_tree.erase(e);
    // ++e;
    // std::cout << (*e).first <<std::endl;
    // std::cout << (*e).first <<std::endl;
    // std::cout << (*e).first <<std::endl;
    // std::cout << (*e).first <<std::endl;
    // std::cout << (*e).first <<std::endl;
  // }
  // while (i != e);

  // s_tree.clear();
  // s_tree.print();
}


///////////////////////////////
#include <iostream>

// int main() {
//   // s21::Map<int, int> m1 = {
//   //     {10, 1},   {20, 2}, {30, 3}, {40, 4},
//   //     {50, 5}, {60, 6},  {70, 7}};

//   s21::Map<std::string, int> m1 = {
//       {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
//       {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"zzz", 10}};

//   std::map<std::string, int> m2 = {
//         {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
//       {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"zzz", 10}};

// //   std::map<int, int> m2 = {
// //       {10, 1}
// // //   };
// //       ,   {20, 2}, {30, 3}, {40, 4},
// //       {50, 5}, {60, 6},  {70, 7}};
// //     // auto iter1 = m1.end();
// //     auto iter2 = m2.end();
// //     ----iter2;
// //     m2.insert_tree({80, 8});
// // //     // v1.insert_tree(iter1, 11);
// // //     v2.insert_tree(iter2, 11);

// // //     for (size_t i = 0; i < v2.size(); ++i) {
// // //       EXPECT_EQ(v2.at(i), v2.at(i));
// // //       std::cout << v2.at(i) << std::endl;
// // //   }

// // //     iter1 = v1.begin();
// // //     iter2 = v2.begin();
// // //     // v1.insert_tree(iter1 + 5, 11);
// // //     v2.insert_tree(iter2 + 5, 1001);

// // //   for (size_t i = 0; i < v2.size(); ++i) {
// // //     EXPECT_EQ(v2.at(i), v2.at(i));
// // //     std::cout << v2.at(i) << std::endl;
// // //   }

//   // for (auto iter1 = m1.begin(); iter1 != m1.end(); ++iter1) {
//     auto iter1 = ++++++++++++++++++++m1.begin();
//     // auto iter1 = --------m1.end();

//   std::cout << iter1.iter->values.first << ' ' << iter1.iter->values.second << std::endl;
//   // }
//   std::cout << '\n' << std::endl;
//   for (auto iter2 = m2.begin(); iter2 != m2.end(); ++iter2) {
//     // EXPECT_EQ(m1.at(i), m2.at(i));
//   std::cout << iter2->first << ' ' << iter2->second << std::endl;
//   }

// // s21::Tree<int, int> t1;
// // t1.print();

// // s21::Map<int, int> m1;
// // m1.insert_tree({24, 1});
// // m1.insert_tree({5, 2});
// // m1.insert_tree({1, 2});
// // m1.insert_tree({15, 2});
// // m1.insert_tree({3, 2});
// // m1.insert_tree({8, 2});
// // // m1.insert_tree({11, 2});
// // m1.print();
// // // auto iter1 = --(++++m1.begin());
// // auto iter1 = m1.begin();
// // auto iter2 = m1.end();

// // --iter2;

// // std::cout << iter1.iter->values.first << std::endl;
// // std::cout << iter2.iter->values.first << std::endl;

// // m1.erase(iter1);
// // iter1 = m1.begin();
// // ++++iter1;
// // m1.erase(iter1);
// // m1.erase(iter2);

// // std::cout << m1.size() << std::endl;

// // iter1 = m1.begin();  //  change after erase
// // iter2 = m1.end();
// // --iter2;
// // std::cout << iter1.iter->values.first << std::endl;
// // std::cout << iter2.iter->values.first << std::endl;

// // m1.print();

// // // std::cout << m2.end()._M_node << std::endl;
// // // std::cout << m2.end()._M_node->_M_left << std::endl;
// // // std::cout << m2.end()._M_node->_M_right << std::endl;
// // // std::cout << m2.end()._M_node->_M_parent << std::endl;
// // // std::cout << (--m2.end())._M_node << std::endl;
// // std::cout << m2.begin()._M_node << std::endl;
// // std::cout << (m2.end())._M_node->_M_left << std::endl;

// // std::cout << (--m2.end())._M_node << std::endl;
// // std::cout << (m2.end())._M_node->_M_right << std::endl;
// // // std::cout << (--m2.end())._M_node->_M_parent << std::endl;
// // // std::cout << (--m2.end())._M_node->_M_left << std::endl;
// // // std::cout << (--m2.end())._M_node->_M_right << std::endl;

// // m2.end();

// return 0;
// }
