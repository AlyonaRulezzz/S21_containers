#include <gtest/gtest.h>
#include <vector>
#include "../s21_vector.h"

TEST(Constructor, Default) {
  s21::Vector<double> v1;
  EXPECT_EQ(0, v1.size());
}

TEST(Constructor, With_parameter) {
  s21::Vector<int> v1(4);
  EXPECT_EQ(4, v1.size());
  EXPECT_EQ(4, v1.capacity());

  EXPECT_ANY_THROW(s21::Vector<int> v2(-4));
}

TEST(Constructor, Initializer_list) {
  std::vector<double> v1 = {1, 2, 3, 4.356, 5.0};
  s21::Vector<double> v2 = {1, 2, 3, 4.356, 5.0};

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(Constructor, Copy) {
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  s21::Vector<int> v1(v2);

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v1.at(i));
  }
}

// TEST(Constructor, Move) {
//   s21::Vector<int> v2 = {1, 2, 3, 4, 5};
//   s21::Vector<int> v1(v2);

//   for (size_t i = 0; i < v1.size(); ++i) {
//     EXPECT_EQ(v1.at(i), v1.at(i));
//   }
// }

TEST(Constructor, Assign_operator) {
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  s21::Vector<int> v1 = v2;

  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v1.at(i));
  }
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(vector_element, at) {
    std::vector<double> v1 = {1.366, 2, 3};
    s21::Vector<double> v2 = {1.366, 2, 3};

    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1.at(i), v2.at(i));
    }
    EXPECT_ANY_THROW(v2.at(-8));
    EXPECT_ANY_THROW(v2.at(3));
}

TEST(vector_element, brackets) {
    std::vector<double> v1 = {1.366, 2, 3};
    s21::Vector<double> v2 = {1.366, 2, 3};
    
    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(vector_element, front_and_back) {
    std::vector<double> v1 = {1.366, 2, 3};
    s21::Vector<double> v2 = {1.366, 2, 3};

    EXPECT_EQ(v1.front(), v2.front());
    EXPECT_EQ(v1.back(), v2.back());
}

TEST(vector_element, data) {
  s21::Vector<int> v1;

  EXPECT_EQ(v1.data(), nullptr);

  std::vector<double> v2 = {1.366, 2, 3, 4, 5};
  s21::Vector<double> v3 = {1.366, 2, 3, 4, 5};

  EXPECT_EQ(*v2.data(), *v3.data());
}

TEST(vector_iterator, begin) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  auto iter1 = v1.begin();
  auto iter2 = v2.begin();

  EXPECT_EQ(*iter1, *iter2);
}

TEST(vector_iterator, end) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  auto iter1 = v1.end();
  auto iter2 = v2.end();

  EXPECT_EQ(*(iter1 - 1), *(iter2 - 1));
}

TEST(Vector_capacity, empty) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(v1.empty(), v2.empty());

  std::vector<int> v3 = {};
  s21::Vector<int> v4 = {};

  EXPECT_EQ(v3.empty(), v4.empty());
}

TEST(Vector_capacity, size) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(v1.size(), v2.size());
}

TEST(Vector_capacity, max_size) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};

  EXPECT_EQ(v1.max_size(), v2.max_size());
}

TEST(Vector_capacity, reserve_and_capacity) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  v1.reserve(30);
  v2.reserve(30);

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  v1.reserve(0);
  v2.reserve(0);

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());

  EXPECT_ANY_THROW(v2.reserve(-7));
}

TEST(Vector_capacity, shrink_to_fit) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  v1.shrink_to_fit();
  v2.shrink_to_fit();

  EXPECT_EQ(v1.size(), v1.capacity());
  EXPECT_EQ(v2.size(), v2.capacity());
}

TEST(Vector_modifier, clear) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::Vector<int> v2 = {1, 2, 3, 4, 5};
  v1.clear();
  v2.clear();

  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(Vector_modifier, insert) {
    s21::Vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto iter1 = v1.begin();
    auto iter2 = v2.begin();
    v1.insert(iter1, 11);
    // v2.insert(iter2, 11);
    // EXPECT_EQ(v1[10], v2[10]);
    // EXPECT_EQ(v1.size(), v2.size());
    // EXPECT_EQ(v1.capacity(), v2.capacity());

    for (size_t i = 0; i < v1.size(); ++i) {
      // EXPECT_EQ(v1.at(i), v2.at(i));
      std::cout << v1.at(i) << std::endl;
    }

    // iter1 = v1.begin();
    // iter2 = v2.begin();
    // v1.insert(iter1 + 5, 11);
    // v2.insert(iter2 + 5, 11);
    // EXPECT_EQ(v1[5], v2[5]);
    // EXPECT_EQ(v1.size(), v2.size());
    // EXPECT_EQ(v1.capacity(), v2.capacity());

    // EXPECT_ANY_THROW(v1.insert(iter1 - 500, 11));
    // EXPECT_ANY_THROW(v1.insert(iter1 + 500, 11));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



///////////////////////////////
#include <iostream>

// int main() {
//     s21::Vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     auto iter1 = v1.end();
//     auto iter2 = v2.end();
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
//   std::cout << *(iter2 + 5) << std::endl;
// }
