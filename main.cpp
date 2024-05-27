#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "myList.hpp"
#include "myInteger.hpp"

TEST(List, smallIncrementIterator) {
  MyList<int> li {5, 7, 9};
  auto it = li.begin();
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 7);
  ++it;
  EXPECT_EQ(*it, 9);
  ++it;
  EXPECT_EQ(it, li.end());
}

TEST(List, smallIncrementMyInteger) {
  MyList<MyInteger> li {MyInteger {5}, MyInteger {7}, MyInteger {9}};
  auto it = li.begin();
  EXPECT_EQ(*it, MyInteger {5});
  ++it;
  EXPECT_EQ(*it, MyInteger {7});
  ++it;
  EXPECT_EQ(*it, MyInteger {9});
  ++it;
  EXPECT_EQ(it, li.end());
}

TEST(List, smallDecrementIterator) {
  MyList<int> li {5, 7, 9};
  auto it = li.end();
  --it;
  EXPECT_EQ(*it, 9);
  --it;
  EXPECT_EQ(*it, 7);
  --it;
  EXPECT_EQ(*it, 5);
  EXPECT_EQ(it, li.begin());
}

TEST(List, smallDecrementMyInteger) {
  MyList<MyInteger> li {MyInteger {5}, MyInteger {7}, MyInteger {9}};
  auto it = li.end();
  --it;
  EXPECT_EQ(*it, MyInteger {9});
  --it;
  EXPECT_EQ(*it, MyInteger {7});
  --it;
  EXPECT_EQ(*it, MyInteger {5});
  EXPECT_EQ(it, li.begin());
}

TEST(List, rangeBasedFor) {
  MyList<int> li {};
  const int N = 100;
  for (int i = 0; i < N; ++i) {
    li.push_back(i);
  }
  int i = 0;
  for (int x : li) {
    EXPECT_EQ(x, i); 
    ++i;
  }
}

TEST(List, rangeBasedForMyInteger) {
  MyList<MyInteger> li {};
  const int N = 100;
  for (int i = 0; i < N; ++i) {
    li.push_back(MyInteger {i});
  }
  int i = 0;
  for (const auto& x : li) {
    EXPECT_EQ(x, MyInteger {i}); 
    ++i;
  }
}

TEST(List, loopWithIterators) {
  MyList<int> li {};
  const int N = 100;
  for (int j = 0; j < N; ++j) {
    li.push_back(j);
  }
  int i = 0;
  for (auto it = li.begin(); it != li.end(); ++it) {
    EXPECT_EQ(*it, i); 
    ++i;
  }
}

TEST(List, reverseIteration) {
  MyList<int> li {};
  const int N = 100;
  for (int j = 0; j < N; ++j) {
    li.push_back(j);
  }
  int i = N;
  for (auto it = li.end(); it != li.begin();) {
    --it;
    --i;
    EXPECT_EQ(*it, i);
  }
}

TEST(List, decrementingFromEnd) {
  MyList<int> li {1, 2, 3};
  MyList<int>::Iterator it = li.end();
  --it;
  EXPECT_EQ(*it, li.back());
}

TEST(List, decrementingFromEndMyInteger) {
  MyList<MyInteger> li {MyInteger {1}, MyInteger {2}, MyInteger {3}};
  auto it = li.end();
  --it;
  EXPECT_EQ(*it, li.back());
}

TEST(List, insertFirst) {
  MyList<int> li {};
  li.push_back(2);
  li.insert(li.begin(), 1);
  EXPECT_EQ(li.size(), 2);
  auto it = li.begin();
  EXPECT_EQ(*it, 1); 
  ++it;
  EXPECT_EQ(*it, 2); 
}

TEST(List, insertLast) {
  MyList<int> li {1, 2, 3};
  auto it = li.end();
  li.insert(it, 4);
  EXPECT_EQ(li.size(), 4);
  it = li.end();
  --it;
  EXPECT_EQ(*it, 4); 
  --it;
  EXPECT_EQ(*it, 3); 
}

TEST(List, insertPenultimate) {
  MyList<int> li {1, 2, 4};
  auto it = li.end();
  --it;
  li.insert(it, 3);
  EXPECT_EQ(li.size(), 4);
  int i = 1;
  for (auto iter = li.begin(); iter != li.end(); ++iter) {
    EXPECT_EQ(*iter, i);
    ++i;
  }
}

TEST(List, insertString) {
  MyList<std::string> li {"Hello", "How", "You", "Doing?"};
  auto it = li.begin();
  ++it;
  ++it;
  li.insert(it, "Are");
  std::vector<std::string> phrase {"Hello", "How", "Are", "You", "Doing?"};
  std::size_t i = 0;
  for (const auto& x : li) {
    EXPECT_EQ(x, phrase.at(i));
    ++i; 
  }
}


TEST(List, insertAlternateOnes) {
  MyList<int> li {0, 0, 0, 0, 0};
  for (auto iter = li.begin(); iter != li.end(); ++iter) {
    li.insert(iter, 1);
  }
  EXPECT_EQ(li.size(), 10);
  int i = 1;
  for (int x : li) {
    EXPECT_EQ(x, i++ % 2);
  }
}

TEST(List, eraseAtFront) {
  MyList<MyInteger> li {MyInteger {0}, MyInteger {1}, MyInteger {2}};
  auto it = li.begin();
  li.erase(it);
  EXPECT_EQ(li.size(), 2);
  EXPECT_EQ(li.front(), MyInteger {1});
}

TEST(List, eraseAtBack) {
  MyList<MyInteger> li {MyInteger {0}, MyInteger {1}, MyInteger {2}};
  auto it = li.end();
  --it;
  li.erase(it);
  EXPECT_EQ(li.size(), 2);
  EXPECT_EQ(li.back(), MyInteger {1});
}

TEST(List, eraseInMiddle) {
  const int N = 10;
  MyList<int> li {};
  for (int i = 0; i < N; ++i) {
    li.push_back(i);
  }
  auto it = li.begin();
  for (int i = 0; i < N/2; ++i) {
    ++it;
  }
  li.erase(it);
  EXPECT_EQ(li.size(), N - 1);
  it = li.begin();
  for (int i = 0; i < N/2 - 1; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  ++it;
  for (int i = N/2 + 1; i < N; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(List, noIteratorInvalidationInsert) {
  MyList<MyInteger> li {MyInteger {0}, MyInteger {1}, MyInteger {2}};
  auto it = li.begin();
  li.insert(it, MyInteger {-1});
  EXPECT_EQ(*it, MyInteger {0});
  EXPECT_EQ(*li.begin(), MyInteger {-1});
}

TEST(List, noIteratorInvalidationErase) {
  MyList<MyInteger> li {MyInteger {0}, MyInteger {1}, MyInteger {2}};
  auto it_begin = li.begin();
  auto it_last = --li.end();
  auto it = li.begin();
  ++it;
  li.erase(it);
  EXPECT_EQ(*it_begin, MyInteger {0});
  EXPECT_EQ(*it_last, MyInteger {2});
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
