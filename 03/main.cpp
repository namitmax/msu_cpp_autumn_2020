#include <iostream>
#include "matrix.hpp"
#include "test_runner.hpp"

void TestBadMatrix() {
  size_t n = 4;
  size_t m = 3;
  Matrix m1(n, m);
  Matrix m2(n, m + 1);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      m1[i][j] = int (i + j);
      m2[i][j] = int (i - j);
    }
  ASSERT_EQUAL(m1 == m2, false)
  int t = 0;
  try {
    Matrix m3(0, 1);
  }
  catch (std::out_of_range& e) {
    t++;
  }
  ASSERT_EQUAL(1, t)
  try {
    m1[3][3] = 0;
  }
  catch (std::out_of_range& e) {
    t++;
  }
  ASSERT_EQUAL(2, t)
  try {
    m1 = m2;
  }
  catch (std::out_of_range& e) {
    t++;
  }
  ASSERT_EQUAL(3, t)
}

void TestOutputMatrix() {
  std::ifstream input("output.txt");
  int temp;
  size_t n = 4;
  size_t m = 3;
  Matrix m3(n, m);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      m3[i][j] = int (4 * 2 * i);
    }
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      input >> temp;
      ASSERT_EQUAL(m3[i][j], temp)
    } 
}

void SimpleTestMatrix() {
  size_t n = 4;
  size_t m = 3;
  Matrix m1(n, m);
  Matrix m2(n, m);
  Matrix m3(n, m);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      m1[i][j] = int (i + j);
      m2[i][j] = int (i - j);
    }
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      ASSERT_EQUAL(m1[i][j], int (i + j))
      ASSERT_EQUAL(m2[i][j], int (i - j))
    }
  ASSERT_EQUAL(m1 == m2, false)
  m3 = m1 + m2;
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      ASSERT_EQUAL(m3[i][j], int (2 * i))
    }
  m3 *= 4;
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++) {
      ASSERT_EQUAL(m3[i][j], int (4 * 2 * i))
    }
  ASSERT_EQUAL((m1 != m3), true)
  ASSERT_EQUAL(m1 == m3, false)
  std::ofstream output("output.txt");
  output << m3;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, SimpleTestMatrix);
  RUN_TEST(tr, TestBadMatrix);
  RUN_TEST(tr, TestOutputMatrix);
  return 0;
}
