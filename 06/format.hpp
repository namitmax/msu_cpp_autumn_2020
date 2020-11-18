#ifndef FORMAT_HPP_
#define FORMAT_HPP_

#include <utility>
#include <sstream>
#include <vector>
#include <string>

class ExtraSymbolException : public std::exception {
  private:
    bool isOpen = true;
    std::string badToken = "";

  public:
    explicit ExtraSymbolException(const bool whatExcept) {
      isOpen = whatExcept;
    }

    const char* what() const noexcept override {
      std::string temp;
      if (isOpen)
        return "There is an extra '{' in token";
      return "There is an extra '}' in token";
    }
};

class ParametrsException : public std::exception {
  public:
    explicit ParametrsException(const bool whatExcept) {
      whatException = whatExcept;
    }

    const char* what() const noexcept override {
      std::string temp;
      if (whatException)
        return "There is an extra symbol in brackets";
      return "There is an extra number in string";
    }

  private:
    bool whatException = true;
    std::string badToken = "";
};

bool isDigit(const std::string& str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (!isdigit(str[i]))
      return false;
  }
  return true;
}

int takeDigit(const std::string& str) {
  return std::stoi(str);
}

template <class T>
std::string makeString(const T& str) {
  std::stringstream input;
  input << str;
  return input.str();
}

template <class... Args>
std::string format(const std::string& str,
                   const Args&... args) {
  std::vector<std::string> temp = { makeString(args)... };
  std::string buf = "", result = "";
  char tempSym;
  bool isOpen = false;
  size_t paramNum = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    tempSym = str[i];
    if (isOpen) {
      if (tempSym == '{') {
        throw ExtraSymbolException(true);
      } else {
        if (tempSym == '}') {
          if (!(isDigit(buf))) {
            throw ParametrsException(true);
          }
          paramNum = takeDigit(buf);
          if (paramNum >= temp.size()) {
            throw ParametrsException(false);
          }
          result += temp[paramNum];
          buf = "";
          isOpen = false;
        } else {
          buf += tempSym;
        }
      }
    } else {
      if (tempSym == '{') {
        isOpen = true;
      } else {
        if (tempSym == '}') {
          throw ExtraSymbolException(false);
        } else {
          result += tempSym;
        }
      }
    }
  }
  if (isOpen)
    throw std::runtime_error("there is an extra '{'");
  return result;
}

#endif  // FORMAT_HPP_
