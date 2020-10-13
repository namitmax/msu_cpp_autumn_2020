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
  Allocator b;
  size_t max = 30;
  b.makeAllocator(max);
  char* t1 = b.alloc(2);
  for (size_t i = 0; i < max; i += 2) {
    ASSERT_EQUAL(t1, b.get_ptr_by_offset(i))
    t1 = b.alloc(2);
  }
  b.reset();
  t1 = b.alloc(max);
  ASSERT_EQUAL(t1, b.get_ptr_by_offset(0))
  ASSERT_EQUAL(b.alloc(1), nullptr)
  b.reset();
  ASSERT_EQUAL(b.alloc(10),  b.get_ptr_by_offset(0))
  ASSERT_EQUAL(b.alloc(10),  b.get_ptr_by_offset(10))
  ASSERT_EQUAL(b.alloc(0), nullptr)
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
  return 0;
}
