#include "test_runner.hpp"
#include "allocator.hpp"

void TestZeroPointer() {
  Allocator a;
  char *test;
  a.makeAllocator(0);
  for (int i = 1; i < 3; i++) {
    test = a.alloc(i);
    a.reset();
    ASSERT_EQUAL(test, nullptr);
  }
  a.makeAllocator(10);
}

void TestDefaultPointer() {
  char *test;
  Allocator b;
  size_t temp = 0;
  size_t max = 30;
  b.makeAllocator(max);
  char* begin = b.alloc(0);
  for (int i = 0; i < 15; i++) {
    test = b.alloc(i);
    temp += i;
    if (temp <= max)
      ASSERT_EQUAL(test, begin + temp)
    else
      ASSERT_EQUAL(test, nullptr);
    if (i % 10 == 0) {
      b.reset();
      temp = 0;
      ASSERT_EQUAL(b.alloc(0), begin);
    }
  }
}

void TestHeapOverflow() {
  Allocator c;
  c.makeAllocator(-1);
  ASSERT_EQUAL(c.alloc(0), nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestZeroPointer);
  RUN_TEST(tr, TestDefaultPointer);
  RUN_TEST(tr, TestHeapOverflow);
  return 0;
}
