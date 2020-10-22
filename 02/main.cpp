#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "parser.hpp"
#include "test_runner.hpp"

void OutputNumber(const int n) {
  std::cout << "Number " << n << "\n";
}

void OutputString(const std::string& str) {
  std::cout << "String " << str << "\n";
}

void OutputStartParsing() {
  std::cout << "Start parsing\n";
}

void OutputEndParsing() {
  std::cout << "End parsing\n";
}

void TestEmptyString() {
  std::string input = "";
  TokenParser parser;
  parser.Parse(input);
  ASSERT_EQUAL(parser.getCallBackLog(0), -1)
  ASSERT_EQUAL(parser.getLog(0), "")
  ASSERT_EQUAL(parser.getIsDigitLog(0), false)
}

void TestDefaultParser() {
  std::string input = "123 456\n        789 123a slkdkdk       fjfjfj\n\n-100";
  TokenParser parser;
  parser.SetStartCallback(OutputStartParsing);
  parser.SetEndCallback(OutputEndParsing);
  parser.SetDigitTokenCallback(OutputNumber);
  parser.SetStringTokenCallback(OutputString);
  parser.Parse(input);
  ASSERT_EQUAL(parser.getCallBackLog(0), 0)
  ASSERT_EQUAL(parser.getLog(0), "123")
  ASSERT_EQUAL(parser.getIsDigitLog(0), true)
  ASSERT_EQUAL(parser.getCallBackLog(1), 2)
  ASSERT_EQUAL(parser.getLog(1), "456")
  ASSERT_EQUAL(parser.getIsDigitLog(1), true)
  ASSERT_EQUAL(parser.getCallBackLog(2), 2)
  ASSERT_EQUAL(parser.getLog(2), "789")
  ASSERT_EQUAL(parser.getIsDigitLog(2), true)
  ASSERT_EQUAL(parser.getCallBackLog(3), 2)
  ASSERT_EQUAL(parser.getLog(3), "123a")
  ASSERT_EQUAL(parser.getIsDigitLog(3), false)
  ASSERT_EQUAL(parser.getCallBackLog(4), 1)
  ASSERT_EQUAL(parser.getLog(4), "slkdkdk")
  ASSERT_EQUAL(parser.getIsDigitLog(4), false)
  ASSERT_EQUAL(parser.getCallBackLog(5), 1)
  ASSERT_EQUAL(parser.getLog(5), "fjfjfj")
  ASSERT_EQUAL(parser.getIsDigitLog(5), false)
  ASSERT_EQUAL(parser.getCallBackLog(6), 1)
  ASSERT_EQUAL(parser.getLog(6), "-100")
  ASSERT_EQUAL(parser.getIsDigitLog(6), false)
  ASSERT_EQUAL(parser.getCallBackLog(7), 1)
  ASSERT_EQUAL(parser.getLog(7), "")
  ASSERT_EQUAL(parser.getIsDigitLog(7), false)
  ASSERT_EQUAL(parser.getCallBackLog(8), 3)
  ASSERT_EQUAL(parser.getCallBackLog(9), -1)
}

void TestNoArgsParser() {
  TokenParser parser;
  std::string input = "123\n456 789	123  456\n\n789		-1	";
  parser.Parse(input);
  ASSERT_EQUAL(parser.getLog(0), "123")
  ASSERT_EQUAL(parser.getIsDigitLog(0), true)
  ASSERT_EQUAL(parser.getLog(1), "456")
  ASSERT_EQUAL(parser.getIsDigitLog(1), true)
  ASSERT_EQUAL(parser.getLog(2), "789")
  ASSERT_EQUAL(parser.getIsDigitLog(2), true)
  ASSERT_EQUAL(parser.getLog(3), "123")
  ASSERT_EQUAL(parser.getIsDigitLog(3), true)
  ASSERT_EQUAL(parser.getLog(4), "456")
  ASSERT_EQUAL(parser.getIsDigitLog(4), true)
  ASSERT_EQUAL(parser.getLog(5), "789")
  ASSERT_EQUAL(parser.getIsDigitLog(5), true)
  ASSERT_EQUAL(parser.getLog(6), "-1")
  ASSERT_EQUAL(parser.getIsDigitLog(6), false)
  ASSERT_EQUAL(parser.getLog(7), "")
  ASSERT_EQUAL(parser.getIsDigitLog(7), false)
  ASSERT_EQUAL(parser.getCallBackLog(0), -1)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoArgsParser);
  std::cout << "-------\n";
  RUN_TEST(tr, TestDefaultParser);
  std::cout << "-------\n";
  RUN_TEST(tr, TestEmptyString);
  return 0;
}
