#include <gtest/gtest.h>
#include <stack>

#include "treemap.h"

TEST(Treemap, Empty) {
  Treemap<int, int> map;

  /* Should be fully empty */
  EXPECT_EQ(map.Empty(), true);
  EXPECT_EQ(map.Size(), 0);
  EXPECT_THROW(map.Get(42), std::exception);
}

TEST(Treemap, OneKey) {
  Treemap<int, char> map;

  /* Test some insertion */
  map.Insert(23, 'A');
  map.Insert(42, 'B');
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(map.MinKey(), 23);
  EXPECT_EQ(map.MaxKey(), 42);
  EXPECT_EQ(map.Get(23), 'A');
}

TEST(Treemap, MulKey) {
  Treemap<int, int> map;

  /* Test some insertions and some deletions */
  map.Insert(1, 69);
  EXPECT_EQ(map.Empty(), false);
  map.Remove(1);
  EXPECT_EQ(map.Empty(), true);

  map.Insert(1, 70);
  map.Insert(3, 41);
  EXPECT_THROW(map.Insert(3, 41), std::exception);
  map.Insert(2, 6);
  map.Insert(8, 7);
  map.Insert(17, 12);
  map.Insert(5, 5);
  EXPECT_THROW(map.Insert(5, 41), std::exception);

  EXPECT_EQ(map.Size(), 6);
  EXPECT_EQ(map.ContainsKey(5), true);
  EXPECT_EQ(map.Get(5), 5);
  EXPECT_EQ(map.MaxKey(), 17);

  EXPECT_THROW(map.Remove(69), std::exception);
  EXPECT_THROW(map.Remove(101), std::exception);
  EXPECT_THROW(map.Remove('A'), std::exception);
  EXPECT_THROW(map.Remove(100000), std::exception);

  map.Remove(1);
  map.Remove(3);

  EXPECT_EQ(map.MinKey(), 2);
  EXPECT_EQ(map.MaxKey(), 17);
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 4);

  EXPECT_THROW(map.Get(1), std::exception);
  EXPECT_THROW(map.Get(3), std::exception);
  EXPECT_EQ(map.Get(17), 12);

  map.Remove(2);
  map.Remove(8);
  EXPECT_EQ(map.Size(), 2);

  map.Insert(100, 10);
  EXPECT_EQ(map.MaxKey(), 100);
  EXPECT_EQ(map.MinKey(), 5);
  EXPECT_EQ(map.Size(), 3);

  map.Remove(17);
  EXPECT_EQ(map.Size(), 2);
  EXPECT_THROW(map.Get(2), std::exception);

  map.Remove(100);
  EXPECT_EQ(map.Empty(), false);
  EXPECT_EQ(map.Size(), 1);
  EXPECT_THROW(map.Remove(100), std::exception);

}

TEST(Treemap, FloorKey) {
  Treemap<int, char> map;
  EXPECT_THROW(map.FloorKey(10), std::exception);

  map.Insert(10, 'A');
  map.Insert(8, 'B');
  map.Insert(12, 'C');

  EXPECT_EQ(map.FloorKey(13), 12);
  EXPECT_EQ(map.FloorKey(12), 12);
  EXPECT_EQ(map.FloorKey(10), 10);
  EXPECT_EQ(map.FloorKey(8), 8);
  EXPECT_THROW(map.FloorKey(7), std::exception);
}

TEST(Treemap, CeilKey) {
  Treemap<int, char> map;

  /* Empty tree check for ceil */
  EXPECT_THROW(map.CeilKey(12), std::exception);
  EXPECT_THROW(map.CeilKey(8), std::exception);
  EXPECT_THROW(map.CeilKey(10), std::exception);

  map.Insert(10, 'A');
  map.Insert(8, 'B');
  map.Insert(12, 'C');

  EXPECT_EQ(map.CeilKey(12), 12);
  EXPECT_EQ(map.CeilKey(10), 10);
  EXPECT_EQ(map.CeilKey(8), 8);
  EXPECT_THROW(map.CeilKey(13), std::exception);
}

TEST(Treemap, MaxKey) {
  Treemap<int, int> map;
  EXPECT_THROW(map.MaxKey(), std::exception);

  map.Insert(101, 10);
  map.Insert(220, 20);
  map.Insert(310, 30);
  map.Insert(411, 40);
  map.Insert(115, 50);
  map.Insert(161, 60);
  map.Insert(127, 70);
  map.Insert(182, 80);
  map.Insert(211, 90);
  map.Insert(111, 100);

  EXPECT_EQ(map.MaxKey(), 411);
  map.Remove(411);
  EXPECT_EQ(map.MaxKey(), 310);
  map.Remove(310);
  EXPECT_EQ(map.MaxKey(), 220);
  map.Remove(220);
  EXPECT_EQ(map.MaxKey(), 211);
}

TEST(Treemap, MinKey) {
  Treemap<int, int> map;
  EXPECT_THROW(map.MinKey(), std::exception);

  map.Insert(101, 10);
  map.Insert(220, 20);
  map.Insert(310, 30);
  map.Insert(411, 40);
  map.Insert(115, 50);
  map.Insert(161, 60);
  map.Insert(127, 70);
  map.Insert(182, 80);
  map.Insert(211, 90);
  map.Insert(111, 100);

  EXPECT_EQ(map.MinKey(), 101);
  map.Remove(101);
  EXPECT_EQ(map.MinKey(), 111);
  map.Remove(111);
  EXPECT_EQ(map.MinKey(), 115);
  map.Remove(115);
  EXPECT_EQ(map.MinKey(), 127);
}

TEST(Treemap, ContainsKey) {
  Treemap<int, int> map;

  map.Insert(1, 100);
  map.Insert(3, 20);
  map.Insert(5, 301);
  map.Insert(7, 4);
  map.Insert(9, 521);
  map.Insert(11, 666);
  map.Insert(13, 470);
  map.Insert(15, 619);
  map.Insert(17, 714);
  map.Insert(19, 100);

  EXPECT_EQ(map.ContainsKey(19), true);
  EXPECT_EQ(map.ContainsKey(20), false);
  EXPECT_EQ(map.ContainsKey(10), false);
  EXPECT_EQ(map.ContainsKey(1), true);
  EXPECT_EQ(map.ContainsKey(11), true);
  EXPECT_EQ(map.ContainsKey(100), false);
  EXPECT_EQ(map.ContainsKey(3), true);
}

TEST(Treemap, ContainsValue) {
  Treemap<int, char> map;

  map.Insert(1, 'A');
  map.Insert(2, 'B');
  map.Insert(3, 'C');
  map.Insert(4, 'D');
  map.Insert(5, 'E');
  map.Insert(6, 'F');
  map.Insert(7, 'G');
  map.Insert(8, 'H');
  map.Insert(9, 'I');
  map.Insert(10, 'J');

  EXPECT_EQ(map.ContainsValue('L'), false);
  EXPECT_EQ(map.ContainsValue('A'), true);
  EXPECT_EQ(map.ContainsValue('W'), false);

  map.Remove(1);
  map.Remove(2);
  map.Remove(3);

  EXPECT_EQ(map.ContainsValue('A'), false);
  EXPECT_EQ(map.ContainsValue('B'), false);
  EXPECT_EQ(map.ContainsValue('C'), false);
  EXPECT_EQ(map.ContainsValue(1), false);
  EXPECT_EQ(map.ContainsValue(2), false);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

