#include <iostream>
#include <string>
#include "test_runner.hpp"
#include "file_sort.hpp"

void SimpleTest1() {
  std::ofstream input("input.txt");
  uint64_t size = 10;
  for (uint64_t i = 0; i < size; ++i) {
    input.write(reinterpret_cast<char *>(&i), sizeof(uint64_t));
  }
  input.close();
  fileSort("input.txt");
  std::ifstream output("output.txt");
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    ASSERT_EQUAL(previous > current, false)
  }
  output.close();
}

void SimpleTest2() {
  std::ofstream input("input.txt");
  uint64_t size = 10;
  uint64_t j;
  for (uint64_t i = 0; i < size; ++i) {
    j = size - i;
    input.write(reinterpret_cast<char *>(&j), sizeof(uint64_t));
  }
  input.close();
  fileSort("input.txt");
  std::ifstream output("output.txt");
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    ASSERT_EQUAL(previous > current, false)
  }
  output.close();
}

void BigTest() {
  std::ofstream input("input.txt");
  uint64_t size = 10000;
  uint64_t j;
  for (uint64_t i = 0; i < size; ++i) {
    j = std::rand() % size;
    input.write(reinterpret_cast<char *>(&j), sizeof(uint64_t));
  }
  input.close();
  fileSort("input.txt");
  std::ifstream output("output.txt");
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    ASSERT_EQUAL(previous > current, false)
  }
  output.close();
}

void VeryBigTest() {
  std::ofstream input("input.txt");
  uint64_t size = 9'000'000;
  uint64_t j;
  for (uint64_t i = 0; i < size; ++i) {
    j = std::rand() % size;
    input.write(reinterpret_cast<char *>(&j), sizeof(uint64_t));
  }
  input.close();
  fileSort("input.txt");
  std::ifstream output("output.txt");
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    ASSERT_EQUAL(previous > current, false)
  }
  output.close();
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, SimpleTest1);
  RUN_TEST(tr, SimpleTest2);
  RUN_TEST(tr, BigTest);
  RUN_TEST(tr, VeryBigTest);
  return 0;
}
