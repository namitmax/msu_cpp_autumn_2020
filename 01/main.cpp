#include "allocator.hpp"
#include "test_runner.hpp"

void TestZeroPointer() {
  Allocator a;
  char *test;
  a.makeAllocator(0);
  for (int i = 1; i < 3; i++) {
    test = a.alloc(i);
    a.reset();
    ASSERT_EQUAL(test, nullptr)
  }
  a.makeAllocator(10);
}

void TestDefaultPointer() {
  char *test;
  Allocator b;
  size_t temp = 0;
  size_t max = 30;
  b.makeAllocator(max);
  ASSERT_EQUAL(b.alloc(0), nullptr)
  char* begin = b.alloc(1);
  for (int i = 0; i < 15; i++) {
    test = b.alloc(i);
    temp += i;
    // printf("%p %p \n", test, begin+temp);
    if ((temp <= max) && (i != 0))
      ASSERT_EQUAL(test, begin + temp)
    else
      ASSERT_EQUAL(test, nullptr)
    if (i % 10 == 0) {
      b.reset();
      temp = 0;
      ASSERT_EQUAL(b.alloc(1), begin)
    }
  }
  b.reset();
  temp = max - 1;
  ASSERT_EQUAL(b.alloc(max), begin + temp)
  ASSERT_EQUAL(b.alloc(max), nullptr)
  b.reset();
  ASSERT_EQUAL(b.alloc(-10), nullptr)
}

void TestHeapOverflow() {
  Allocator c;
  c.makeAllocator(-1);
  ASSERT_EQUAL(c.alloc(1), nullptr)
  ASSERT_EQUAL(c.alloc(10), nullptr)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestZeroPointer);
  RUN_TEST(tr, TestDefaultPointer);
  RUN_TEST(tr, TestHeapOverflow);
  return 0;
}
