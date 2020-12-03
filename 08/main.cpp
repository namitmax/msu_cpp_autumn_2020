#include <iostream>
#include <string>
#include "test_runner.hpp"
#include "threadPool.hpp"

struct A {
  int a = 5;
};

struct B {
  std::string b;
};

int fooA(const A& temp) {
  return temp.a;
}

int fooI(const int i) {
  return i;
}

std::string fooB(const B& temp) {
  return temp.b;
}

void MoreThreadsTest() {
  ThreadPool pool(10);
  std::vector<int> log;
  for (int i = 0; i < 10; ++i) {
    auto taskI = pool.exec(fooI, i);
    log.push_back(taskI.get());
  }
  ASSERT_EQUAL(log, std::vector({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}))
  log.clear();
  ThreadPool pool1(20);
  for (int i = 0; i < 10; ++i) {
    auto taskI = pool1.exec(fooI, i);
    log.push_back(taskI.get());
  }
  ASSERT_EQUAL(log, std::vector({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}))
}

void SimpleTest() {
  ThreadPool pool(8);
  auto task1 = pool.exec(fooA, A());
  ASSERT_EQUAL(5, task1.get())
  auto task2 = pool.exec([]() { return 1; });
  B temp;
  temp.b = "word";
  auto task3 = pool.exec(fooB, temp);
  std::string word = task3.get();
  ASSERT_EQUAL(word, "word")
  ASSERT_EQUAL(1, task2.get())
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, SimpleTest);
  RUN_TEST(tr, MoreThreadsTest);
  return 0;
}
