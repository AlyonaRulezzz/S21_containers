#include <gtest/gtest.h>

#include <set>
#include <initializer_list>

#include "../s21_tree.h"

#include "../s21_multiset.h"
#include "../iterators/multiset_iterator.h"
// #include "../iterators/set_iterator.h"

#include <vector>
#include <iostream>

TEST(MultisetConstructor, Default) {
  s21::Multiset<std::string> s;
  std::multiset<std::string> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MultisetIterator, initializer_list_operator_dereferencing_plusplus_minusminus_begin_end) {
  s21::Multiset<int> s = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};

  std::multiset<int> b = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};

  auto si = s.begin();
  auto bi = b.begin();
  for (; si != s.end() && bi != b.end(); ++si, ++bi) {
    EXPECT_EQ((*si), (*bi));
  }

  si = s.end();
  bi = b.end();
  ----si;
  ----bi;
    EXPECT_EQ((*si), (*bi));

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MultisetConstructors, Copy) {
  s21::Multiset<int> s_tree = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};
  // s21::Multiset<int>& cp_s_tree = s_tree;
  s21::Multiset<int>& cp_s_tree(s_tree);

  std::multiset<int> o_tree = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};
  std::multiset<int> cp_o_tree = o_tree;

  auto si = cp_s_tree.begin();
  auto oi = cp_o_tree.begin();
  for (; si != cp_s_tree.end() && oi != cp_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(cp_s_tree.size(), cp_o_tree.size());
  EXPECT_EQ(cp_s_tree.empty(), cp_o_tree.empty());
}

TEST(MultisetConstructors, Move) {
  s21::Multiset<int> s_tree = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};
  s21::Multiset<int> mv_s_tree = std::move(s_tree);

  std::multiset<int> o_tree = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};
  std::multiset<int> mv_o_tree = std::move(o_tree);

  auto si = mv_s_tree.begin();
  auto oi = mv_o_tree.begin();
  for (; si != mv_s_tree.end() && oi != mv_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  EXPECT_EQ(mv_s_tree.size(), mv_o_tree.size());
  EXPECT_EQ(mv_s_tree.empty(), mv_o_tree.empty());

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());
}

TEST(MultisetConstructors, Operator_equal) {
  s21::Multiset<int> m1 = {
      {10},   {20}, {30}, {40},
      {50}, {60},  {70}};

  s21::Multiset<int>& m2 = m1;

  auto e = m1.end(); --e; auto i = m1.end();
  do {
    ++i;
    EXPECT_EQ((*i), (*i));
  }
  while (i != e);

  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(FixErase, Erase) {
  s21::Multiset<std::string> s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> o_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  // ++++++++++++++++si;
  // ++++++++++++++++oi;
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  // auto s_it = s_tree.begin();
  // auto o_it = o_tree.begin();
  // ++ ++ ++ ++s_it;
  // ++ ++ ++ ++o_it;
  auto s_it = s_tree.end();
  auto o_it = o_tree.end();
  --s_it; --o_it;

  s_tree.erase(s_it);
  o_tree.erase(o_it);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  si = s_tree.begin();
  oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}


TEST(MultisetLookup, Find) {
  s21::Multiset<std::string> s1 = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> s2 = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  EXPECT_EQ(*s1.find("zero"), *s2.find("zero"));
  EXPECT_EQ(*s1.find("seven"), *s2.find("seven"));
  // std::cout << &(*s1.find("seventy"));
  // std::cout << &(*s2.find("seventy"));
  // EXPECT_EQ(&(*s1.find("seventy")), &(*s2.find("seventy")));
}


TEST(MultisetLookup, Contains) {
  s21::Multiset<std::string> s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  EXPECT_EQ(s_tree.contains("zero"), true);
  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

TEST(MultisetModifiers, Insert) {  //  NEED TO FIX THIS
  // s21::Multiset<double> v = {1,  1, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
  //                             26,  8, 8,  8};
  // std::multiset<double> vc = { 1,  1, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
  //                             26, 8, 8,  8};

  s21::Multiset<double> v = {1,  1, 2, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
                              26,  8, 8,  8};
  std::multiset<double> vc = { 1,  1, 2, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 8, 8,  8};
  v.insert_m(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  // v.print();
  for (; y != vc.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }




//   // s21::Multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
//   // std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
//   // v.insert(15);
//   // vc.insert(15);
//   // v.erase(v.begin());
//   // vc.erase(vc.begin());
//   // auto x = v.begin();
//   // auto y = vc.begin();
//   // for (; y != vc.end(); ++x, ++y) {
//   //   ASSERT_EQ(*x, *y);
//   // }
//     s21::Multiset<std::string> s_tree
//   // ;
//    = {
//       {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
//       {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

//   std::multiset<std::string> o_tree 
//   // ;
//   = {
//       {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
//       {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

//   EXPECT_EQ(s_tree.size(), o_tree.size());
//   EXPECT_EQ(s_tree.empty(), o_tree.empty());

//   s_tree.clear();
//   o_tree.clear();

//   auto s_pr = s_tree.insert({"one"});
//   auto o_pr = o_tree.insert("one");
//   EXPECT_EQ(*(s_pr.first), (*o_pr.first));
//   EXPECT_EQ(s_pr.second, o_pr.second);

//   s_pr = s_tree.insert({"ten", 10});
//   o_pr = o_tree.insert({"ten", 10});
//   EXPECT_EQ(*(s_pr.first), (*o_pr.first));
//   EXPECT_EQ(s_pr.second, o_pr.second);

//   s_pr = s_tree.insert({"twelve", 20});
//   o_pr = o_tree.insert({"twelve", 20});
//   EXPECT_EQ(*(s_pr.first), (*o_pr.first));
//   EXPECT_EQ(s_pr.second, o_pr.second);

//   s_pr = s_tree.insert({"thirty", 30});
//   o_pr = o_tree.insert({"thirty", 30});
//   EXPECT_EQ(*(s_pr.first), (*o_pr.first));
//   EXPECT_EQ(s_pr.second, o_pr.second);

//   auto si = s_tree.begin();
//   auto oi = o_tree.begin();
//   for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
//     EXPECT_EQ(*(si), *(oi));
//   }

//   EXPECT_EQ(s_tree.size(), o_tree.size());
//   EXPECT_EQ(s_tree.empty(), o_tree.empty());
}


TEST(FixErase, Swap) {
  s21::Multiset<std::string> f_s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  s21::Multiset<std::string> s_s_tree = {
      {"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
      {"fifty"}, {"sixty"},  {"seventy"}};

  std::multiset<std::string> f_o_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> s_o_tree = {
      {"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
      {"fifty"}, {"sixty"},  {"seventy"}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());
    // std::cout << "\n" << "f_s_tree.size()=" << f_s_tree.size() << "\n\n";

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  f_s_tree.swap(s_s_tree);
  f_o_tree.swap(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());
    // std::cout << "\n" << "f_s_tree.size()=" << f_s_tree.size() << "\n\n";
    // std::cout << "\n" << "s_s_tree.size()=" << s_s_tree.size() << "\n\n";


  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(FixErase, Merge) {
  s21::Multiset<int> m1a {{1}, {5}, {10}};
  s21::Multiset<int> m1b {{2}, {4}, {5}, {8}};
  s21::Multiset<int> u1;

  std::multiset<int> m2a {{1}, {5}, {10}};
  std::multiset<int> m2b {{2}, {4}, {5}, {8}};
  std::multiset<int> u2;
  u1.merge(m1a);
  u2.merge(m2a);

  auto i1 = u1.begin();
  auto i2 = u2.begin();
  for (; i1 != u1.end() && i2 != u2.end(); ++i1, ++i2) {
    EXPECT_EQ((*i1), (*i2));
  }

  s21::Multiset<std::string> f_s_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  s21::Multiset<std::string> s_s_tree = {
      {"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
      {"fifty"}, {"sixty"},  {"seventy"}};

  std::multiset<std::string> f_o_tree = {
      {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
      {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

  std::multiset<std::string> s_o_tree = {
      {"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
      {"fifty"}, {"sixty"},  {"seventy"}};

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  auto si = f_s_tree.begin();
  auto oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }

  f_s_tree.merge(s_s_tree);
  f_o_tree.merge(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
  // si = s_s_tree.begin(); //  cos now it is empty
  oi = s_o_tree.begin();
  // std::cout << (*oi).second;
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si), (*oi));
  }
}

TEST(YSetCapacity, Max_size) {
  s21::Multiset<std::string> s = {
      {"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
      {"fifty"}, {"sixty"},  {"seventy"}};
  std::multiset<std::string> b = {
      {"ten"},   {"twenty"}, {"thirty"}, {"fourty"},
      {"fifty"}, {"sixty"},  {"seventy"}};

  EXPECT_EQ(s.max_size(), b.max_size());
}

TEST(MultisetLookup, Count) {  //  NEED TO FIX THIS
  // s21::Multiset<double> v = {1,  1, 1, 2,  -3, 20, -5, 1, -6, 8, 42,  //  NEED TO FIX THIS
  //                             26,  8, 8,  8};
  // std::multiset<double> vc = { 1,  1, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
  //                             26, 8, 8,  8};

  s21::Multiset<double> v = { 1,  1, 2, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
                              26,  8, 8,  8};
  std::multiset<double> vc = { 1,  1, 2, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 8, 8,  8};

  EXPECT_EQ(v.count(1), vc.count(1));
  EXPECT_EQ(v.count(2), vc.count(2));
  EXPECT_EQ(v.count(8), vc.count(8));
  EXPECT_EQ(v.count(-6), vc.count(-6));
  EXPECT_EQ(v.count(-100), vc.count(-100));
}

TEST(MultisetLookup, Lower_bound) {
  s21::Multiset<double> v = /* {2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 1,  1,  1,  8, 8,  8}; */
                              { 1,  1, 2, 1, 2,  -3, 20, -5, 1, -6, 8, 42,
                              26,  8, 8,  8};
                              // {1, 3, 5, 8, 15, 24};
  // auto x = v.lower_bound(8);
  // --x;
  ASSERT_EQ(*(v.lower_bound(8)), 8);
  ASSERT_EQ(*(v.lower_bound(2)), 2);
  ASSERT_EQ(*(v.lower_bound(-3)), -3);
  ASSERT_EQ(*(v.lower_bound(20)), 20);

  ASSERT_EQ(*(v.lower_bound(-2)), 1);
  ASSERT_EQ(*(v.lower_bound(38)), 42);
  ASSERT_EQ(*(v.lower_bound(-12)), -6);

  // ASSERT_EQ(*(v.lower_bound(43)), 0);
}


// TEST(MultisetModifiers, Emplace) {
//   s21::Multiset<std::string> s_tree = {
//       {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
//       {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

//   std::multiset<std::string> o_tree = {
//       {"zero"}, {"one"}, {"two"},   {"three"}, {"four"},
//       {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}};

//   EXPECT_EQ(s_tree.size(), o_tree.size());
//   EXPECT_EQ(s_tree.empty(), o_tree.empty());

//   auto v = s_tree.emplace("eleven",
//                           "twelve",
//                           "nine",
//                           "thirteen");

//   auto p0 = o_tree.emplace("eleven");
//   auto p1 = o_tree.emplace("twelve");
//   auto p2 = o_tree.emplace("nine");
//   auto p3 = o_tree.emplace("thirteen");

//   EXPECT_EQ((*(v[0].first)), (*(p0.first)));
//   EXPECT_EQ(v[0].second, p0.second);

//   EXPECT_EQ((*(v[1].first)), (*(p1.first)));
//   EXPECT_EQ(v[1].second, p1.second);

//   EXPECT_EQ((*(v[2].first)), (*(p2.first)));
//   EXPECT_EQ(v[2].second, p2.second);

//   EXPECT_EQ((*(v[3].first)), (*(p3.first)));
//   EXPECT_EQ(v[3].second, p3.second);

//   EXPECT_EQ(s_tree.size(), o_tree.size());
//   EXPECT_EQ(s_tree.empty(), o_tree.empty());

//   auto si = s_tree.begin();
//   auto oi = o_tree.begin();
//   for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
//     EXPECT_EQ((*si), (*oi));
//   }
// }


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();


  // s21::Multiset<std::string> m = {
  //     {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
  //     {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  // std::cout << m.search("ninety");
}
