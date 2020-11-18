#include <fstream>
#include "test_runner.hpp"
#include "format.hpp"

void BadTest() {
  std::string text = "";
  int k = 0;
  try {
    text = format("{1}+{1} = {0}", 2);
  } catch (const std::exception& err) {
    k++;
  }
  ASSERT_EQUAL(k, 1)
  try {
    text = format("{1}+{1} = {0} }", 2, 1);
  } catch (const std::exception& err) {
    k++;
  }
  ASSERT_EQUAL(k, 2)
  try {
    text = format("{1}+{1} = {0} {", 2, 1);
  } catch (const std::exception& err) {
    k++;
  }
  ASSERT_EQUAL(k, 3)
  try {
    text = format("{1}+{1} = {0adf}", 2, 1);
  } catch (const std::exception& err) {
    k++;
  }
  ASSERT_EQUAL(k, 4)
}

void FileOutput() {
  std::ofstream output("output.txt");
  output << format("({2}+{0})*{1}", 10, 15, 30);
}

void OutputTest() {
  FileOutput();
  std::ifstream input("output.txt");
  std::string temp;
  input >> temp;
  ASSERT_EQUAL(temp, "(30+10)*15");
}

void SimpleTest() {
  auto text = format("{1}+{1} = {0}", 2, "one");
  ASSERT_EQUAL(text, "one+one = 2");
  ASSERT_EQUAL(format("{001}{0}", 0, 1), "10");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, OutputTest);
  RUN_TEST(tr, SimpleTest);
  RUN_TEST(tr, BadTest);
  return 0;
}
