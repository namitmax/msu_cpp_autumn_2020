#include <string>
#include <cstring>
#include <iostream>
#include "parser.hpp"
#include "test_runner.hpp"

void OutputNumber(const int n) {
  std::cout << "Number " << n << "\n";
}

void OutputString(const char* str) {
  std::cout << "String " << str << "\n";
}

void OutputStartParsing() {
  std::cout << "Start parsing\n";
}

void OutputEndParsing() {
  std::cout << "End parsing\n";
}

void TestDefaultParser() {
  std::string input = "123 456\n        789 123a slkdkdk       fjfjfj\n\n-100";
  TokenParser parser;
  parser.SetStartCallback(OutputStartParsing);
  parser.SetEndCallback(OutputEndParsing);
  parser.SetDigitTokenCallback(OutputNumber);
  parser.SetStringTokenCallback(OutputString);
  parser.Parse(input);
}

void TestNoArgsParser() {
  TokenParser parser;
  std::string input = "123	456\n789 123a slkdkdk	 fjfjfj\n\n-100";
  parser.Parse(input);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoArgsParser);
  printf("-------\n");
  RUN_TEST(tr, TestDefaultParser);
  return 0;
}
