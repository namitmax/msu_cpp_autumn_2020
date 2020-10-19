#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <functional>
#include <string>
#include <cstring>
#include <sstream>

using StringToken = std::function<void (const std::string& str)>;
using DigitToken  = std::function<void (const int number)>;
using StartParse  = std::function<void ()>;
using EndParse    = std::function<void ()>;

class TokenParser {
  private:
    StringToken stringCallback;
    DigitToken  digitCallback;
    StartParse  startParsingCallback;
    EndParse    endParsingCallback;

    bool isDigit(const std::string& str, int* number) {
      int temp;
      for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]))
          return false;
      }
      std::istringstream inputDigit(str);
      if (!(inputDigit >> temp))
        return false;
      *number = temp;
      return true;
    }

    void ProcessToken(const std::string& temp) {
      int number;
      if (temp != "") {
        if (!(isDigit(temp, &number))) {
          if (stringCallback != nullptr)
            stringCallback(temp);
          else
            std::cout << "There is no some special callback for string\n";
        } else {
          if (digitCallback != nullptr)
            digitCallback(number);
          else
            std::cout << "There is no some special callback for digit\n";
        }
      }
    }

  public:
    TokenParser():
      stringCallback(nullptr),
      digitCallback(nullptr),
      startParsingCallback(nullptr),
      endParsingCallback(nullptr) {}

    ~TokenParser() {}

    void Parse(const std::string& input) {
      if (startParsingCallback != nullptr)
        startParsingCallback();
      else
        std::cout << "There is no some special callback for start parsing\n";
      std::string delims = " \n\t";
      std::string str = input;
      std::string temp;
      size_t current, previous = 0;
      current = str.find_first_of(delims);
      while (current != std::string::npos) {
        temp = str.substr(previous, current - previous);
        ProcessToken(temp);
        previous = current + 1;
        current = str.find_first_of(delims, previous);
      }
      temp = str.substr(previous, str.size() - previous);
      ProcessToken(temp);
      if (endParsingCallback != nullptr)
        endParsingCallback();
      else
        std::cout << "There is no some special callback for end parsing\n";
    }

    void SetStartCallback(StartParse someCallback) {
      startParsingCallback = someCallback;
    }

    void SetEndCallback(EndParse someCallback) {
      endParsingCallback = someCallback;
    }

    void SetDigitTokenCallback(DigitToken someCallback) {
      digitCallback = someCallback;
    }

    void SetStringTokenCallback(StringToken someCallback) {
      stringCallback = someCallback;
    }
};

#endif  // PARSER_HPP_
