#include "../s21_containers_test.h"

TEST(multiset, defaultConstructor) {
  s21::multiset<int> s21IntMultiset;
  s21::multiset<char> s21CharMultiset;
  s21::multiset<double> s21DoubleMultiset;
  std::multiset<int> stlIntMultiset;
  std::multiset<char> stlCharMultiset;
  std::multiset<double> stlDoubleMultiset;

  EXPECT_EQ(s21IntMultiset.empty(), stlIntMultiset.empty());
  EXPECT_EQ(s21CharMultiset.empty(), stlCharMultiset.empty());
  EXPECT_EQ(s21DoubleMultiset.empty(), stlDoubleMultiset.empty());
}

TEST(multiset, initializerConstructor1) {
  s21::multiset<int> s21EmptyMultiset{};
  std::multiset<int> stlEmptyMultiset{};
  auto s21Iter = s21EmptyMultiset.begin();
  auto stlIter = stlEmptyMultiset.begin();
  auto s21IterEnd = s21EmptyMultiset.end();

  EXPECT_EQ(s21EmptyMultiset.size(), stlEmptyMultiset.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, initializerConstructor2) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 4, 5, 6, 7};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 4, 5, 6, 7};
  auto s21Iter = s21Multiset.begin();
  auto stlIter = stlMultiset.begin();
  auto s21IterEnd = s21Multiset.end();

  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, initializerConstructor3) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  auto s21Iter = s21Multiset.begin();
  auto stlIter = stlMultiset.begin();
  auto s21IterEnd = s21Multiset.end();

  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, copyConstructor) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  s21::multiset<int> s21MultisetCopy = s21Multiset;
  std::multiset<int> stlMultisetCopy = stlMultiset;
  auto s21Iter = s21MultisetCopy.begin();
  auto stlIter = stlMultisetCopy.begin();
  auto s21IterEnd = s21MultisetCopy.end();

  EXPECT_EQ(s21MultisetCopy.size(), stlMultisetCopy.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, moveConstructor) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  s21::multiset<int> s21MultisetMove = s21Multiset;
  std::multiset<int> stlMultisetMove = stlMultiset;
  auto s21Iter = s21MultisetMove.begin();
  auto stlIter = stlMultisetMove.begin();
  auto s21IterEnd = s21MultisetMove.end();
  EXPECT_EQ(s21MultisetMove.size(), stlMultisetMove.size());
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, begin) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  auto s21Iter = s21Multiset.begin();
  auto stlIter = stlMultiset.begin();

  EXPECT_EQ(*s21Iter, *stlIter);
  s21Iter++;
  stlIter++;
  EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, end) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  auto s21Iter = s21Multiset.end();
  auto stlIter = stlMultiset.end();

  s21Iter--;
  stlIter--;
  EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, empty) {
  s21::multiset<int> s21EmptyMultiset{};
  std::multiset<int> stlEmptyMultiset{};
  EXPECT_EQ(s21EmptyMultiset.empty(), stlEmptyMultiset.empty());
}

TEST(multiset, size) {
  s21::multiset<int> s21Multiset{};
  std::multiset<int> stlMultiset{};

  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());
  s21Multiset.insert(1);
  stlMultiset.insert(1);
  EXPECT_EQ(s21Multiset.empty(), stlMultiset.empty());
  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());
}

TEST(multiset, max_size) {
  s21::multiset<int> s21Multiset{};
  auto maxSize = s21Multiset.max_size();
  EXPECT_GT(maxSize, 0);
}

TEST(multiset, clear) {
  s21::multiset<int> s21Multiset{};
  std::multiset<int> stlMultiset{};

  EXPECT_EQ(s21Multiset.empty(), stlMultiset.empty());
  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());

  s21Multiset.insert(1);
  stlMultiset.insert(1);
  EXPECT_EQ(s21Multiset.empty(), stlMultiset.empty());
  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());

  s21Multiset.clear();
  stlMultiset.clear();
  EXPECT_EQ(s21Multiset.empty(), stlMultiset.empty());
  EXPECT_EQ(s21Multiset.size(), stlMultiset.size());
}

TEST(multiset, insert) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  auto s21InsertResult = s21Multiset.insert(4);
  auto stlInsertResult = stlMultiset.insert(4);
  EXPECT_EQ(s21Multiset.count(4), stlMultiset.count(4));
  EXPECT_TRUE(*s21InsertResult == *stlInsertResult);

  s21InsertResult = s21Multiset.insert(1);
  stlInsertResult = stlMultiset.insert(1);
  EXPECT_EQ(s21Multiset.count(1), stlMultiset.count(1));
  EXPECT_TRUE(*s21InsertResult == *stlInsertResult);
}

TEST(multiset, erase) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  auto size = s21Multiset.size();
  auto itEnd = s21Multiset.end();
  itEnd--;
  s21Multiset.erase(itEnd);
  auto new_size = s21Multiset.size();

  EXPECT_NE(size, new_size);
  s21Multiset.erase(s21Multiset.begin());
  stlMultiset.erase(stlMultiset.begin());
  auto s21Iter = s21Multiset.begin();
  auto stlIter = stlMultiset.begin();
  auto s21IterEnd = s21Multiset.end();

  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multiset, swap) {
  s21::multiset<int> s21Multiset{0, 1, 2};
  s21::multiset<int> s21SwapMultiset{3, 3, 4, 5, 7, 6, 6};

  s21Multiset.swap(s21SwapMultiset);

  EXPECT_EQ(s21Multiset.size(), 7);
  EXPECT_EQ(s21SwapMultiset.size(), 3);
  EXPECT_EQ(*s21Multiset.begin(), 3);
  EXPECT_EQ(*s21SwapMultiset.begin(), 0);
}

TEST(multiset, merge) {
  s21::multiset<int> s21Multiset{0, 1, 2};
  s21::multiset<int> s21MergeMultiset{3, 3, 4, 5, 7, 6, 6};
  s21Multiset.merge(s21MergeMultiset);
  std::multiset<int> stlMultiset{0, 1, 2};
  std::multiset<int> stlMergeMultiset{3, 3, 4, 5, 7, 6, 6};
  stlMultiset.merge(stlMergeMultiset);

  auto s21Iter = s21Multiset.begin();
  auto stlIter = stlMultiset.begin();
  auto s21IterEnd = s21Multiset.end();
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
  EXPECT_EQ(stlMultiset.size(), s21Multiset.size());
  EXPECT_EQ(s21MergeMultiset.size(), stlMergeMultiset.size());
}

TEST(multiset, count) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  EXPECT_EQ(s21Multiset.count(3), stlMultiset.count(3));
  EXPECT_EQ(s21Multiset.count(0), stlMultiset.count(0));
  EXPECT_EQ(s21Multiset.count(4), stlMultiset.count(4));
}

TEST(multiset, find) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  auto s21Iter = s21Multiset.find(3);
  auto stlIter = stlMultiset.find(3);
  auto s21Iter2 = s21Multiset.find(4);

  EXPECT_EQ(*s21Iter, *stlIter);
  EXPECT_EQ(*s21Iter2, *s21Multiset.end());
}

TEST(multiset, contains) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  auto isContains1 = s21Multiset.contains(4);
  auto isContains2 = s21Multiset.contains(1);

  EXPECT_EQ(isContains1, false);
  EXPECT_EQ(isContains2, true);
}

TEST(multiset, equal_range) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  auto s21Range = s21Multiset.equal_range(3);
  auto stlRange = stlMultiset.equal_range(3);

  EXPECT_EQ(*s21Range.first--, *stlRange.first--);
  EXPECT_EQ(*s21Range.second, *stlRange.second);
}

TEST(multiset, lower_bound) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  auto s21Iter = s21Multiset.lower_bound(3);
  auto stlIter = stlMultiset.lower_bound(3);

  EXPECT_EQ(*s21Iter--, *stlIter--);
}

TEST(multiset, upper_bound) {
  s21::multiset<int> s21Multiset{0, 1, 2, 3, 3, 1, 6, 7, 6};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  auto s21Iter = s21Multiset.upper_bound(3);
  auto stlIter = stlMultiset.upper_bound(3);

  EXPECT_EQ(*s21Iter, *stlIter);
}

TEST(multitest, insertMany) {
  s21::multiset<int> s21Multiset{};
  std::multiset<int> stlMultiset{0, 1, 2, 3, 3, 1, 6, 7, 6};

  s21Multiset.insert_many(0, 1, 2, 3, 3, 1, 6, 7, 6);

  auto s21Iter = s21Multiset.begin();
  auto stlIter = stlMultiset.begin();
  auto s21IterEnd = s21Multiset.end();
  for (; s21Iter != s21IterEnd; ++s21Iter, ++stlIter)
    EXPECT_EQ(*s21Iter, *stlIter);
}