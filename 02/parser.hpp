#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <cstring>

using StringToken = void(*)(const char* str);
using DigitToken  = void(*)(const int number);
using StartParse  = void(*)();
using EndParse    = void(*)();

class TokenParser {
  private:
    StringToken stringCallback;
    DigitToken  digitCallback;
    StartParse  startParsingCallback;
    EndParse    endParsingCallback;

    bool isDigit(const char* str, int* number) {
      size_t n = strlen(str);
      int temp;
      for (size_t i = 0; i < n; i++) {
        if (!strchr("0123456789", str[i]))
          return false;
      }
      if (sscanf(str, "%d", &temp) != 1)
        return false;
      *number = temp;
      return true;
    }

  public:
    TokenParser():
      stringCallback(nullptr),
      digitCallback(nullptr),
      startParsingCallback(nullptr),
      endParsingCallback(nullptr) {}

    ~TokenParser() {}

    void Parse(const std::string input) {
      if (startParsingCallback != nullptr)
        startParsingCallback();
      else
        printf("There is no some special callback for start parsing\n");
      char *temp = new char[input.length() + 1];
      int number;
      strcpy(temp, input.c_str());
      char *token = strtok(temp, " \n\t");
      while (token != NULL) {
        if (!(isDigit(token, &number))) {
          if (stringCallback != nullptr)
            stringCallback(token);
          else
            printf("There is no some special callback for string\n");
        } else {
          if (digitCallback != nullptr)
            digitCallback(number);
          else
            printf("There is no some special callback for digit\n");
        }
        token = strtok(NULL, " \n\t");
      }
      if (endParsingCallback != nullptr)
        endParsingCallback();
      else
        printf("There is no some special callback for end parsing\n");
      delete [] temp;
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
