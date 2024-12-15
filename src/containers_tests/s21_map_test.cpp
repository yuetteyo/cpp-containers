#include <map>

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

TEST(map, defaultConstructor) {
  s21::map<int, int> s21IntIntMap;
  s21::map<int, char> s21IntCharMap;
  s21::map<char, double> s21CharDoubleMap;
  s21::map<double, Point> s21DoubleClassMap;
  s21::map<Point, s21::map<int, int>> s21ClassContainerMap;
  std::map<int, int> stlIntIntMap;
  std::map<int, char> stlIntCharMap;
  std::map<char, double> stlCharDoubleMap;
  std::map<double, Point> stlDoubleClassMap;
  std::map<Point, std::map<int, int>> stlClassContainerMap;

  EXPECT_EQ(s21IntIntMap.empty(), stlIntIntMap.empty());
  EXPECT_EQ(s21IntCharMap.empty(), stlIntCharMap.empty());
  EXPECT_EQ(s21CharDoubleMap.empty(), stlCharDoubleMap.empty());
  EXPECT_EQ(s21DoubleClassMap.empty(), stlDoubleClassMap.empty());
  EXPECT_EQ(s21ClassContainerMap.empty(), stlClassContainerMap.empty());
}

TEST(map, initializerConstructor1) {
  s21::map<int, int> s21EmptyMap{};
  std::map<int, int> stlEmptyMap{};
  auto s21Iter = s21EmptyMap.begin();
  auto stlIter = stlEmptyMap.begin();
  auto s21IterEnd = s21EmptyMap.end();

  EXPECT_EQ(s21EmptyMap.size(), stlEmptyMap.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, initializerConstructor2) {
  s21::map<int, int> s21IntIntMap{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> stlIntIntMap{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto s21Iter = s21IntIntMap.begin();
  auto stlIter = stlIntIntMap.begin();
  auto s21IterEnd = s21IntIntMap.end();

  EXPECT_EQ(s21IntIntMap.size(), stlIntIntMap.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, initializerConstructor3) {
  s21::map<int, char> s21IntCharMap{
      {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}};
  std::map<int, char> stlIntCharMap{
      {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}};
  auto s21Iter = s21IntCharMap.begin();
  auto stlIter = stlIntCharMap.begin();
  auto s21IterEnd = s21IntCharMap.end();

  EXPECT_EQ(s21IntCharMap.size(), stlIntCharMap.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, initializerConstructor4) {
  s21::map<char, double> s21CharDoubleMap{
      {'1', 1.1}, {'2', 2.2}, {'3', 3.3}, {'4', 4.4}, {'5', 5.5}};
  std::map<char, double> stlCharDoubleMap{
      {'1', 1.1}, {'2', 2.2}, {'3', 3.3}, {'4', 4.4}, {'5', 5.5}};
  auto s21Iter = s21CharDoubleMap.begin();
  auto stlIter = stlCharDoubleMap.begin();
  auto s21IterEnd = s21CharDoubleMap.end();

  EXPECT_EQ(s21CharDoubleMap.size(), stlCharDoubleMap.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, copyConstructor) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> s21MapCopy = s21Map;
  std::map<int, int> stlMapCopy = stlMap;
  auto s21Iter = s21MapCopy.begin();
  auto stlIter = stlMapCopy.begin();
  auto s21IterEnd = s21MapCopy.end();

  EXPECT_EQ(s21MapCopy.size(), stlMapCopy.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, moveConstructor) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int> s21MapMoved = std::move(s21Map);
  std::map<int, int> stlMapMoved = std::move(stlMap);
  auto s21Iter = s21MapMoved.begin();
  auto stlIter = stlMapMoved.begin();
  auto s21IterEnd = s21MapMoved.end();

  EXPECT_EQ(s21MapMoved.size(), stlMapMoved.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, begin) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto s21Iter = s21Map.begin();
  auto stlIter = stlMap.begin();

  EXPECT_EQ(*s21Iter, (*stlIter).second);
  s21Iter++;
  stlIter++;
  EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, end) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto s21Iter = s21Map.end();
  auto stlIter = stlMap.end();

  s21Iter--;
  stlIter--;
  EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, empty) {
  s21::map<int, int> s21EmptyMap{};
  std::map<int, int> stlEmptyMap{};

  EXPECT_EQ(s21EmptyMap.empty(), stlEmptyMap.empty());
}

TEST(map, size) {
  s21::map<int, int> s21Map{};
  std::map<int, int> stlMap{};

  EXPECT_EQ(s21Map.size(), stlMap.size());
  s21Map.insert(1, 1);
  stlMap.insert({1, 1});
  EXPECT_EQ(s21Map.empty(), stlMap.empty());
  EXPECT_EQ(s21Map.size(), stlMap.size());
}

TEST(map, max_size) {
  s21::map<int, int> s21Map;

  auto maxSize = s21Map.max_size();

  EXPECT_GT(maxSize, 0);
}

TEST(map, clear) {
  s21::map<int, int> s21Map;
  std::map<int, int> stlMap;

  EXPECT_EQ(s21Map.empty(), stlMap.empty());
  EXPECT_EQ(s21Map.size(), stlMap.size());

  s21Map.insert({1, 1});
  stlMap.insert({1, 1});
  EXPECT_EQ(s21Map.empty(), stlMap.empty());
  EXPECT_EQ(s21Map.size(), stlMap.size());

  s21Map.clear();
  stlMap.clear();
  EXPECT_EQ(s21Map.empty(), stlMap.empty());
  EXPECT_EQ(s21Map.size(), stlMap.size());
}

TEST(map, insertPair) {
  s21::map<int, int> s21Map{{2, 2}, {3, 3}, {5, 5}};
  std::map<int, int> stlMap{{2, 2}, {3, 3}, {5, 5}};

  auto s21InsertResult = s21Map.insert({6, 6});
  auto stlInsertResult = stlMap.insert({6, 6});
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);
  s21InsertResult = s21Map.insert({1, 1});
  stlInsertResult = stlMap.insert({1, 1});
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);
  s21InsertResult = s21Map.insert({4, 4});
  stlInsertResult = stlMap.insert({4, 4});
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);
}

TEST(map, insert) {
  s21::map<int, int> s21Map{{2, 2}, {3, 3}, {5, 5}};
  std::map<int, int> stlMap{{2, 2}, {3, 3}, {5, 5}};

  auto s21InsertResult = s21Map.insert(6, 6);
  auto stlInsertResult = stlMap.insert({6, 6});
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);
  s21InsertResult = s21Map.insert(1, 1);
  stlInsertResult = stlMap.insert({1, 1});
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);
  s21InsertResult = s21Map.insert(4, 4);
  stlInsertResult = stlMap.insert({4, 4});
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);
}

TEST(map, insertOrAssign) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {5, 5}};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {5, 5}};

  auto s21InsertResult = s21Map.insert_or_assign(6, 6);
  auto stlInsertResult = stlMap.insert_or_assign(6, 6);
  EXPECT_TRUE(s21InsertResult.second == stlInsertResult.second);
  EXPECT_TRUE(*s21InsertResult.first == (*stlInsertResult.first).second);

  auto s21AssignResult = s21Map.insert_or_assign(1, 2);
  auto stlAssignResult = stlMap.insert_or_assign(1, 2);
  EXPECT_TRUE(s21AssignResult.second == stlAssignResult.second);
  EXPECT_TRUE(*s21AssignResult.first == (*stlAssignResult.first).second);
}

TEST(map, erase) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {5, 5}};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {5, 5}};
  auto size = s21Map.size();
  auto itEnd = s21Map.end();
  itEnd--;
  s21Map.erase(itEnd);
  auto new_size = s21Map.size();

  EXPECT_NE(size, new_size);
  s21Map.erase(s21Map.begin());
  stlMap.erase(stlMap.begin());
  auto s21Iter = s21Map.begin();
  auto stlIter = stlMap.begin();
  auto s21IterEnd = s21Map.end();

  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}

TEST(map, swap) {
  s21::map<int, int> s21Map = {{1, 1}};
  s21::map<int, int> s21SwapMap = {{3, 3}, {4, 4}, {5, 5}};

  s21Map.swap(s21SwapMap);
  EXPECT_EQ(s21Map.size(), 3);
  EXPECT_EQ(s21SwapMap.size(), 1);
  EXPECT_EQ(*s21Map.begin(), 3);
  EXPECT_EQ(*s21SwapMap.begin(), 1);
}

TEST(map, merge) {
  s21::map<int, int> s21Map = {{1, 1}};
  s21::map<int, int> s21MergeMap = {{3, 3}, {4, 4}, {5, 5}};
  s21Map.merge(s21MergeMap);
  std::map<int, int> stlMap = {{1, 1}};
  std::map<int, int> stlMergeMap = {{3, 3}, {4, 4}, {5, 5}};
  stlMap.merge(stlMergeMap);
  auto s21Iter = s21Map.begin();
  auto stlIter = stlMap.begin();
  auto s21IterEnd = s21Map.end();

  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
  EXPECT_EQ(stlMap.size(), s21Map.size());
  EXPECT_EQ(s21MergeMap.size(), stlMergeMap.size());
}

TEST(map, contains) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {5, 5}};

  auto isContains1 = s21Map.contains(6);
  auto isContains2 = s21Map.contains(1);

  EXPECT_EQ(isContains1, false);
  EXPECT_EQ(isContains2, true);
}

TEST(map, elementAccess) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {5, 5}};
  auto& item = s21Map.at(1);
  EXPECT_EQ(item, 1);
  EXPECT_ANY_THROW(s21Map.at(0));
}

TEST(map, elementAccessOperator) {
  s21::map<int, int> s21Map{{1, 1}, {2, 2}, {3, 3}, {5, 5}};
  auto& item = s21Map[1];
  EXPECT_EQ(item, 1);
  EXPECT_EQ(s21Map[4], 0);
  EXPECT_EQ(s21Map[6] = 6, 6);
}

TEST(map, insertMany) {
  s21::map<int, int> s21Map{};
  std::map<int, int> stlMap{{1, 1}, {2, 2}, {3, 3}, {5, 5}};
  s21Map.insert_many(std::pair<int, int>(1, 1), std::pair<int, int>(2, 2),
                     std::pair<int, int>(3, 3), std::pair<int, int>(5, 5));

  auto s21Iter = s21Map.begin();
  auto stlIter = stlMap.begin();
  auto s21IterEnd = s21Map.end();
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, (*stlIter).second);
}