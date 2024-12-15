#include <set>

#include "../s21_containers_test.h"

TEST(set, constructorInitializer) {
  s21::set<char> setMy{'a', 'b', 'c'};
  std::set<char> setBase{'a', 'b', 'c'};
  auto iterMy = setMy.begin();
  auto iterBase = setBase.begin();
  auto iterMyEnd = setMy.end();

  EXPECT_EQ(setMy.size(), setBase.size());
  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase)
    EXPECT_TRUE(*iterBase == *iterMy);
}

TEST(set, constructorInitializer2) {
  s21::set<char> setMy{};
  std::set<char> setBase{};
  auto iterMy = setMy.begin();
  auto iterBase = setBase.begin();
  auto iterMyEnd = setMy.end();

  EXPECT_EQ(setMy.size(), setBase.size());
  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase)
    EXPECT_EQ(*iterMy, *iterBase);
}

TEST(set, constructorCopy) {
  s21::set<int> setMy{1, 2, 3, 4, 5};
  std::set<int> setBase{1, 2, 3, 4, 5};
  s21::set<int> setMyCopy = setMy;
  std::set<int> setBaseCopy = setBase;
  auto iterMy = setMyCopy.begin();
  auto iterBase = setBaseCopy.begin();
  auto iterMyEnd = setMyCopy.end();

  EXPECT_EQ(setMyCopy.size(), setBaseCopy.size());
  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase)
    EXPECT_EQ(*iterMy, *iterBase);
}

TEST(set, constructorMove) {
  s21::set<int> setMy{1, 2, 3, 4, 5};
  std::set<int> setBase{1, 2, 3, 4, 5};
  s21::set<int> setMyMoved = std::move(setMy);
  std::set<int> setBaseMoved = std::move(setBase);
  auto iterMy = setMyMoved.begin();
  auto iterBase = setBaseMoved.begin();
  auto iterMyEnd = setMyMoved.end();

  EXPECT_EQ(setMy.size(), setBase.size());
  EXPECT_EQ(setMyMoved.size(), setBaseMoved.size());
  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase)
    EXPECT_EQ(*iterMy, *iterBase);
}

TEST(set, begin) {
  s21::set<std::string> setMy{"This", "is", "my", "set"};
  std::set<std::string> setBase{"This", "is", "my", "set"};
  auto iterMy = setMy.begin();
  auto iterBase = setBase.begin();

  EXPECT_EQ(*iterMy, *iterBase);
  iterMy++;
  iterBase++;
  EXPECT_EQ(*iterMy, *iterBase);
}

TEST(set, end) {
  s21::set<std::string> setMy{"This", "is", "my", "set"};
  std::set<std::string> setBase{"This", "is", "my", "set"};

  auto iterMy = setMy.end();
  auto iterBase = setBase.end();

  iterMy--;
  iterBase--;
  EXPECT_EQ(*iterMy, *iterBase);
}

TEST(set, constructorDefault) {
  s21::set<char> setMy;
  std::set<char> setBase;
  auto isEmpty = setMy.empty();

  EXPECT_EQ(isEmpty, setBase.empty());
}

TEST(set, size) {
  s21::set<char> setMy;
  std::set<char> setBase;

  EXPECT_EQ(setMy.empty(), setBase.empty());
  EXPECT_EQ(setMy.size(), setBase.size());
  setMy.insert('b');
  setBase.insert('c');

  EXPECT_EQ(setMy.empty(), setBase.empty());
  EXPECT_EQ(setMy.size(), setBase.size());
}

TEST(set, max_size) {
  s21::set<double> setMy;
  std::set<double> setBase;

  auto maxSize = setMy.max_size();

  EXPECT_GT(maxSize, 0);
}

TEST(set, clear) {
  s21::set<char> setMy;
  std::set<char> setBase;
  setMy.clear();
  setBase.clear();

  EXPECT_EQ(setMy.empty(), setBase.empty());
  EXPECT_EQ(setMy.size(), setBase.size());
  setMy.insert('a');
  setBase.insert('b');
  EXPECT_EQ(setMy.empty(), setBase.empty());
  EXPECT_EQ(setMy.size(), setBase.size());
  setMy.clear();
  setBase.clear();
  EXPECT_EQ(setMy.empty(), setBase.empty());
  EXPECT_EQ(setMy.size(), setBase.size());
}

TEST(set, insert) {
  s21::set<std::string> setMy = {"This", "is", "my", "set"};
  std::set<std::string> setBase = {"This", "is", "my", "set"};

  auto inserResultMy = setMy.insert("best");
  auto insertResultBase = setBase.insert("best");
  EXPECT_TRUE(inserResultMy.second == insertResultBase.second);
  EXPECT_TRUE(*inserResultMy.first == *insertResultBase.first);
  inserResultMy = setMy.insert("is");
  insertResultBase = setBase.insert("is");
  EXPECT_TRUE(inserResultMy.second == insertResultBase.second);
  EXPECT_TRUE(*inserResultMy.first == *insertResultBase.first);
}

TEST(set, erase) {
  s21::set<int> setMy = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> setBase = {5, 4, 3, 2, 7, 8, 9};
  auto size = setMy.size();
  auto itEnd = setMy.end();
  itEnd--;
  setMy.erase(itEnd);
  auto new_size = setMy.size();

  EXPECT_NE(size, new_size);
  setMy.erase(setMy.begin());
  setBase.erase(setBase.begin());
  auto iterMy = setMy.begin();
  auto iterBase = setBase.begin();
  auto iterMyEnd = setMy.end();

  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase) {
    EXPECT_EQ(*iterMy, *iterBase);
  }
}

TEST(set, swap) {
  s21::set<int> setMy = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  setMy.swap(my_swap_set);

  EXPECT_EQ(setMy.size(), 3);
  EXPECT_EQ(my_swap_set.size(), 1);
  EXPECT_EQ(*setMy.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(set, merge) {
  s21::set<int> setMy = {1};
  s21::set<int> setMyForMerge = {3, 4, 5};

  setMy.merge(setMyForMerge);
  std::set<int> setBase = {1};
  std::set<int> setBaseForMerge = {3, 4, 5};

  setBase.merge(setBaseForMerge);
  auto iterMy = setMy.begin();
  auto iterBase = setBase.begin();
  auto iterMyEnd = setMy.end();

  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase)
    EXPECT_EQ(*iterMy, *iterBase);
  EXPECT_EQ(setBase.size(), setMy.size());
  EXPECT_EQ(setMyForMerge.size(), setBaseForMerge.size());
}

TEST(set, find) {
  s21::set<double> setMy = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> setBase = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};

  auto iterMy1 = setMy.find(2.4);
  auto iterBase1 = setBase.find(2.4);
  auto iterMy2 = setMy.find(2.);
  auto iterBase2 = setBase.find(2.);

  EXPECT_EQ(*iterMy1, *iterBase1);
  EXPECT_EQ(*iterMy2, *iterBase2);
}

TEST(set, contains) {
  s21::set<double> setMy = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> setBase = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};

  auto isContains1 = setMy.contains(2.);
  auto isContains2 = setMy.contains(2.1);

  EXPECT_EQ(isContains1, false);
  EXPECT_EQ(isContains2, true);
}

TEST(set, insertMany) {
  s21::set<int> setMy = {};
  std::set<int> setBase = {2, 3, 4, 5, 6, 7};

  setMy.insert_many(2, 3, 4, 5, 6, 7);
  auto iterMy = setMy.begin();
  auto iterBase = setBase.begin();
  auto iterMyEnd = setMy.end();
  for (; iterMy != iterMyEnd; ++iterMy, ++iterBase)
    EXPECT_EQ(*iterMy, *iterBase);
}