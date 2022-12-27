#include <gtest/gtest.h>

#include <map>
#include <initializer_list>

#include "../s21_tree.h"

#include "../s21_map.h"
#include "../iterators/map_iterator.h"

#include <vector>
#include <iostream>

TEST(MapConstructor, Default) {
  s21::Map<std::string, int> s;
  std::map<std::string, int> b;

  EXPECT_EQ(s.size(), b.size());
  EXPECT_EQ(s.empty(), b.empty());
}

TEST(MapIterator, initializer_list_operator_dereferencing_plusplus_minusminus_begin_end) {
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

TEST(FixErase, Erase) {
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

  // s_tree["SSD"]
  // ;
  // = "yyyyy";
  EXPECT_EQ(s_tree["SSD"], o_tree["SSD"]);
}

TEST(MapLookup, Contains) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.contains("zero"), true);
  EXPECT_EQ(s_tree.contains("seven"), true);
  EXPECT_EQ(s_tree.contains("seventy"), false);
}

// TEST(MapDop, Search) {
//   s21::Map<std::string, int> s_tree = {
//       {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
//       {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

//   EXPECT_EQ(s_tree.contains("zero"), true);
//   EXPECT_EQ(s_tree.contains("seven"), true);
//   EXPECT_EQ(s_tree.contains("seventy"), false);
// }

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

  s_tree.clear();
  o_tree.clear();

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

  s_tree.clear();
  o_tree.clear();

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
    // std::cout << "\n" << "f_s_tree.size()=" << f_s_tree.size() << "\n\n";

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
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  si = s_s_tree.begin();
  oi = s_o_tree.begin();
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(FixErase, Merge) {
  s21::Map<int, std::string> m1a {{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::Map<int, std::string> m1b {{2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  s21::Map<int, std::string> u1;

  std::map<int, std::string> m2a {{1, "apple"}, {5, "pear"}, {10, "banana"}};
  std::map<int, std::string> m2b {{2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  std::map<int, std::string> u2;
  u1.merge(m1a);
  u2.merge(m2a);

  auto i1 = u1.begin();
  auto i2 = u2.begin();
  for (; i1 != u1.end() && i2 != u2.end(); ++i1, ++i2) {
    EXPECT_EQ((*i1).first, (*i2).first);
    EXPECT_EQ((*i1).second, (*i2).second);
  }

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

  f_s_tree.merge(s_s_tree);
  f_o_tree.merge(s_o_tree);

  EXPECT_EQ(f_s_tree.size(), f_o_tree.size());
  EXPECT_EQ(f_s_tree.empty(), f_o_tree.empty());
  EXPECT_EQ(s_s_tree.size(), s_o_tree.size());
  EXPECT_EQ(s_s_tree.empty(), s_o_tree.empty());

  si = f_s_tree.begin();
  oi = f_o_tree.begin();
  for (; si != f_s_tree.end() && oi != f_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
  // si = s_s_tree.begin(); //  cos now it is empty
  oi = s_o_tree.begin();
  // std::cout << (*oi).second;
  for (; si != s_s_tree.end() && oi != s_o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}

TEST(YMapCapacity, Max_size) {
  s21::Map<std::string, int> s = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};
  std::map<std::string, int> b = {
      {"ten", 10},   {"twenty", 20}, {"thirty", 30}, {"fourty", 40},
      {"fifty", 50}, {"sixty", 60},  {"seventy", 70}};

  EXPECT_EQ(s.max_size(), b.max_size());
}

TEST(MapModifiers, Emplace) {
  s21::Map<std::string, int> s_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::map<std::string, int> o_tree = {
      {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto v = s_tree.emplace(std::pair<std::string, int>{"eleven", 11},
                          std::pair<std::string, int>{"twelve", 12},
                          std::pair<std::string, int>{"nine", 13},
                          std::pair<std::string, int>{"thirteen", 13});

  auto p1 = o_tree.emplace("eleven", 11);
  auto p2 = o_tree.emplace("twelve", 12);
  auto p3 = o_tree.emplace("nine", 13);
  auto p4 = o_tree.emplace("thirteen", 13);

  EXPECT_EQ((*(v[0].first)).first, (*(p1.first)).first);
  EXPECT_EQ((*(v[0].first)).second, (*(p1.first)).second);
  EXPECT_EQ(v[0].second, p1.second);

  EXPECT_EQ((*(v[1].first)).first, (*(p2.first)).first);
  EXPECT_EQ((*(v[1].first)).second, (*(p2.first)).second);
  EXPECT_EQ(v[1].second, p2.second);

  EXPECT_EQ((*(v[2].first)).first, (*(p3.first)).first);
  EXPECT_EQ((*(v[2].first)).second, (*(p3.first)).second);
  EXPECT_EQ(v[2].second, p3.second);

  EXPECT_EQ((*(v[3].first)).first, (*(p4.first)).first);
  EXPECT_EQ((*(v[3].first)).second, (*(p4.first)).second);
  EXPECT_EQ(v[3].second, p4.second);

  EXPECT_EQ(s_tree.size(), o_tree.size());
  EXPECT_EQ(s_tree.empty(), o_tree.empty());

  auto si = s_tree.begin();
  auto oi = o_tree.begin();
  for (; si != s_tree.end() && oi != o_tree.end(); ++si, ++oi) {
    EXPECT_EQ((*si).first, (*oi).first);
    EXPECT_EQ((*si).second, (*oi).second);
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();


  // s21::Map<std::string, int> m = {
  //     {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
  //     {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  // std::cout << m.search("ninety");
}
