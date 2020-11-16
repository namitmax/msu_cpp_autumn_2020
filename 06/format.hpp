#ifndef FORMAT_HPP_
#define FORMAT_HPP_

#include <utility>
#include <sstream>
#include <vector>
#include <string>

bool isDigit(const std::string& str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (!isdigit(str[i]))
      return false;
  }
  return true;
}

int takeDigit(const std::string& str) {
  int temp;
  std::istringstream inputDigit(str);
  inputDigit >> temp;
  return temp;
}

template <class T>
std::string makeString(T&& str) {
  std::stringstream input;
  input << str;
  return input.str();
}

template <class... Args>
std::string format(const std::string& str,
                   Args&&... args) {
  std::vector<std::string> temp = { makeString(std::forward<Args>(args))... };
  std::string buf = "", result = "";
  char t;
  bool flag = false;
  size_t n = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    t = str[i];
    if (flag) {
      if (t == '{') {
        throw std::runtime_error("extra '{'");
      } else {
        if (t == '}') {
          if (!(isDigit(buf))) {
            throw std::runtime_error("there is an extra symbol in brackets");
          }
          n = takeDigit(buf);
          if (n >= temp.size()) {
            throw std::runtime_error("there is an extra number in string");
          }
          result += temp[n];
          buf = "";
          flag = false;
        } else {
          buf += t;
        }
      }
    } else {
      if (t == '{') {
        flag = true;
      } else {
        if (t == '}') {
          throw std::runtime_error("there is an extra '}'");
        } else {
          result += t;
        }
      }
    }
  }
  if (flag)
    throw std::runtime_error("there is an extra '{'");
  return result;
}

#endif  // FORMAT_HPP_
