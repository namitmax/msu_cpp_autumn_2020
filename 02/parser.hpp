#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <functional>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <vector>

using StringToken = std::function<void (const std::string& str)>;
using DigitToken  = std::function<void (const int number)>;
using StartParse  = std::function<void ()>;
using EndParse    = std::function<void ()>;

class TokenParser {
  private:
    StringToken              stringCallback;
    DigitToken               digitCallback;
    StartParse               startParsingCallback;
    EndParse                 endParsingCallback;
    std::vector<std::string> log;
    std::vector<bool>        isDigitLog;
    std::vector<int>         callBackLog;

    bool isDigit(const std::string& str) {
      for (size_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]))
          return false;
      }
      return true;
    }

    int GetDigit(const std::string& str) {
      int temp;
      std::istringstream inputDigit(str);
      inputDigit >> temp;
      return temp;
    }

    void ProcessToken(const std::string& temp) {
      if (temp != "") {
        log.push_back(temp);
        if (!(isDigit(temp))) {
          isDigitLog.push_back(false);
          if (stringCallback != nullptr) {
            stringCallback(temp);
            callBackLog.push_back(1);
          } else {
            std::cout << "There is no some special callback for string\n";
          }
        } else {
          isDigitLog.push_back(true);
          if (digitCallback != nullptr) {
            digitCallback(GetDigit(temp));
            callBackLog.push_back(2);
          } else {
            std::cout << "There is no some special callback for digit\n";
          }
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
      if (startParsingCallback != nullptr) {
        startParsingCallback();
        callBackLog.push_back(0);
      } else {
        std::cout << "There is no some special callback for start parsing\n";
      }
      std::string delims = " \n\t";
      size_t current, previous = 0;
      current = input.find_first_of(delims);
      while (current != std::string::npos) {
        ProcessToken(input.substr(previous, current - previous));
        previous = current + 1;
        current = input.find_first_of(delims, previous);
      }
      ProcessToken(input.substr(previous, input.size() - previous));
      log.push_back("");
      isDigitLog.push_back(false);
      if (endParsingCallback != nullptr) {
        endParsingCallback();
        callBackLog.push_back(3);
      } else {
        std::cout << "There is no some special callback for end parsing\n";
      }
      callBackLog.push_back(-1);
    }

    int getCallBackLog(const size_t i) {
      return callBackLog[i];
    }

    std::string getLog(const size_t i) {
      return log[i];
    }

    bool getIsDigitLog(const size_t i) {
      return isDigitLog[i];
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
