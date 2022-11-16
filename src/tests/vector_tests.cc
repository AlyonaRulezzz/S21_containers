#include <gtest/gtest.h>
#include <vector>
#include "../s21_vector.h"

TEST(Constructors, Default) {
  // s21::Vector<int> v1();
  // EXPECT_EQ(0, (*v1).size());
  // EXPECT_EQ(0, (*v1).capacity());
  // EXPECT_EQ(nullptr, v1.GetArr());
}

// TEST(Constructors, With_parameters) {
//   s21::Vector<int> m1(4, 5);
//   EXPECT_EQ(4, m1.GetSize());
//   EXPECT_EQ(5, m1.GetCapacity());
//   EXPECT_NO_THROW(s21::Vector<int> m1(4, 5));

//   EXPECT_ANY_THROW(s21::Vector<int> m2(0, 8));
//   EXPECT_ANY_THROW(s21::Vector<int>(-8, 8));
// }

// TEST(Constructors, Copy) {
//   s21::Vector<int> test1;
//   test1.Fill(5);

//   s21::Vector<int> m1(test1);
//   EXPECT_EQ(test1.GetSize(), m1.GetSize());
//   EXPECT_EQ(test1.GetCapacity(), m1.GetCapacity());
//   for (int i = 0; i < m1.GetSize(); i++) {
//     for (int j = 0; j < m1.GetCapacity(); j++) {
//       EXPECT_EQ(test1(i, j), m1(i, j));
//     }
//   }
// }

// TEST(Constructors, Move) {
//   s21::Vector<int> test1(4, 5);
//   test1.Fill(0, 2);
//   s21::Vector<int> res1(test1);
//   s21::Vector<int> m1(std::move(test1));
//   EXPECT_EQ(m1.GetSize(), res1.GetSize());
//   EXPECT_EQ(m1.GetCapacity(), res1.GetCapacity());
//   EXPECT_EQ(true, m1.EqMatrix(res1));
//   EXPECT_EQ(false, m1.EqMatrix(test1));
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
