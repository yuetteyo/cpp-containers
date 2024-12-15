#include <array>
#include <iostream>

#include "../s21_containers_test.h"

class Point {
 public:
  Point(double x = 0, double y = 0) : x_(x), y_(y) {}
  bool operator<(const Point& other) const {
    return (x_ * x_ + y_ * y_) < (other.x_ * other.x_ + other.y_ * other.y_);
  }
  bool operator>(const Point& other) const {
    return (x_ * x_ + y_ * y_) > (other.x_ * other.x_ + other.y_ * other.y_);
  }
  bool operator==(const Point& other) const {
    return x_ == other.x_ && y_ == other.y_;
  }

 private:
  double x_, y_;
};

TEST(array, defaultConstructor) {
  s21::array<int, 10> s21Array{};
  std::array<int, 10> stlArray{};

  for (auto s21It = s21Array.begin(), s21End = s21Array.end(),
            stlIt = stlArray.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, defaultConstructor2) {
  s21::array<int, 0> s21Array{};
  std::array<int, 0> stlArray{};

  for (auto s21It = s21Array.begin(), s21End = s21Array.end(),
            stlIt = stlArray.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, defaultConstructor3) {
  s21::array<Point, 5> s21Array{};
  std::array<Point, 5> stlArray{};

  for (auto s21It = s21Array.begin(), s21End = s21Array.end(),
            stlIt = stlArray.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, initializerConstructor) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  std::array<int, 5> stlArray{1, 2, 3, 4, 5};

  for (auto s21It = s21Array.begin(), s21End = s21Array.end(),
            stlIt = stlArray.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, initializerConstructor2) {
  s21::array<int, 5> s21Array{1, 2, 3};
  std::array<int, 5> stlArray{1, 2, 3};

  for (auto s21It = s21Array.begin(), s21End = s21Array.end(),
            stlIt = stlArray.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, copyConstructor) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  std::array<int, 5> stlArray{1, 2, 3, 4, 5};
  s21::array<int, 5> s21ArrayCopy = s21Array;
  std::array<int, 5> stlArrayCopy = stlArray;

  for (auto s21It = s21ArrayCopy.begin(), s21End = s21ArrayCopy.end(),
            stlIt = stlArrayCopy.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, moveConstructor) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  std::array<int, 5> stlArray{1, 2, 3, 4, 5};
  s21::array<int, 5> s21ArrayMoved = std::move(s21Array);
  std::array<int, 5> stlArrayMoved = std::move(stlArray);

  for (auto s21It = s21ArrayMoved.begin(), s21End = s21ArrayMoved.end(),
            stlIt = stlArrayMoved.begin();
       s21It < s21End; s21It++, stlIt++) {
    EXPECT_EQ(*s21It, *stlIt);
  }
}

TEST(array, elementAccessAt) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  auto& item = s21Array.at(0);
  EXPECT_EQ(item, 1);
  EXPECT_ANY_THROW(s21Array.at(5));
}

TEST(array, elementAccessOperator) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  auto& item = s21Array[0];
  EXPECT_EQ(item, 1);
  EXPECT_EQ(s21Array[3], 4);
  EXPECT_EQ(s21Array[4] = 6, 6);
}

TEST(array, elementAccess) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  std::array<int, 5> stlArray{1, 2, 3, 4, 5};
  EXPECT_EQ(s21Array.front(), stlArray.front());
  EXPECT_EQ(s21Array.back(), stlArray.back());
  EXPECT_EQ(*s21Array.data(), *stlArray.data());
}

TEST(array, begin) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  std::array<int, 5> stlArray{1, 2, 3, 4, 5};
  auto s21Iter = s21Array.begin();
  auto stlIter = stlArray.begin();

  EXPECT_EQ(*s21Iter, *stlIter);
  s21Iter++;
  stlIter++;
  EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(array, end) {
  s21::array<int, 5> s21Array{1, 2, 3, 4, 5};
  std::array<int, 5> stlArray{1, 2, 3, 4, 5};
  auto s21Iter = s21Array.end();
  auto stlIter = stlArray.end();

  s21Iter--;
  stlIter--;
  EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(array, empty) {
  s21::array<int, 0> s21EmptyArray{};
  std::array<int, 0> stlEmptyArray{};
  EXPECT_EQ(s21EmptyArray.empty(), stlEmptyArray.empty());
}

TEST(array, empty2) {
  s21::array<int, 4> s21Array{};
  std::array<int, 4> stlArray{};
  EXPECT_EQ(s21Array.empty(), stlArray.empty());
}

TEST(array, size) {
  s21::array<int, 0> s21Array{};
  std::array<int, 0> stlArray{};

  EXPECT_EQ(s21Array.size(), stlArray.size());
}

TEST(array, size2) {
  s21::array<int, 4> s21Array{};
  std::array<int, 4> stlArray{};

  EXPECT_EQ(s21Array.size(), stlArray.size());
}

TEST(array, max_size) {
  const size_t size = 4;
  s21::array<int, size> s21Array{};
  auto maxSize = s21Array.max_size();
  EXPECT_EQ(maxSize, size);
}

TEST(array, swap) {
  s21::array<int, 3> s21Array{1, 2, 3};
  s21::array<int, 3> s21SwapArray{4, 5, 6};

  s21Array.swap(s21SwapArray);
  EXPECT_EQ(*s21Array.begin(), 4);
  EXPECT_EQ(*s21SwapArray.begin(), 1);
}

TEST(array, swap2) {
  s21::array<int, 3> s21Array{1, 2, 3};
  s21::array<int, 3> s21SwapArray{4, 5, 6};
  std::array<int, 3> stlArray{1, 2, 3};
  std::array<int, 3> stlSwapArray{4, 5, 6};
  auto s21It = s21Array.begin();
  auto s21ItSwap = s21SwapArray.begin();
  auto stlIt = stlArray.begin();
  auto stlItSwap = stlSwapArray.begin();
  s21Array.swap(s21SwapArray);
  stlArray.swap(stlSwapArray);
  EXPECT_EQ(*s21It, *stlIt);
  EXPECT_EQ(*s21ItSwap, *stlItSwap);
}

TEST(array, fill) {
  s21::array<int, 10> s21Array{};
  int value = 9;
  s21Array.fill(value);
  for (auto i : s21Array) EXPECT_EQ(i, 9);
}