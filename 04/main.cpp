#include <iostream>
#include <fstream>
#include "bigInt.hpp"
#include "test_runner.hpp"

void FillFile() {
  std::ofstream output("output.txt");
  BigInt a;
  for (int i = -15; i < 16; i++) {
    a = i;
    output << a << "\n";
  }
}

void OutputTest() {
  FillFile();
  std::ifstream input("output.txt");
  int a;
  for (int i = -15; i < 16; i++) {
    input >> a;
    ASSERT_EQUAL(a, i)
  }
}

void ConstructorTest() {
  BigInt a1("100");
  BigInt a2 = std::move(a1);
  ASSERT_EQUAL(a1.isEmpty(), true)
  ASSERT_EQUAL(a2, 100)
  BigInt a3 = 300;
  a2 = std::move(a3);
  ASSERT_EQUAL(a3.isEmpty(), true)
  ASSERT_EQUAL(a2, 300)
}

void SimpleTest() {
  int n = 30;
  int m = 40;
  BigInt res;
  BigInt a1 = 50;
  BigInt a2 = 50;
  ASSERT_EQUAL(a1 + a2, 100)
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      res = i + j;
      ASSERT_EQUAL(res, i + j)
      res *= i;
      ASSERT_EQUAL(res, (i + j) * i)
      res -= i * i;
      ASSERT_EQUAL(res, i * j)
      res = -100 * i + j;
      res *= 2;
      ASSERT_EQUAL(res, -200 * i + 2 * j)
      ASSERT_EQUAL(-res, 200 * i - 2 * j)
      // если бы - менял состояние res, то этот тест не был бы пройден
      ASSERT_EQUAL(res, -200 * i + 2 * j)
    }
}

void BigTest() {
  BigInt a1("12345678901234567890123456789");
  BigInt a2(123);
  BigInt result("1518518504851851850485185185047");
  ASSERT_EQUAL(a1 * a2, result)
  ASSERT_EQUAL(a1 < result, true)
  ASSERT_EQUAL(a1 * a2 * -1, -result)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, ConstructorTest);
  RUN_TEST(tr, SimpleTest);
  RUN_TEST(tr, OutputTest);
  RUN_TEST(tr, BigTest);
  return 0;
}
