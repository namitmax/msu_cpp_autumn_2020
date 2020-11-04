#ifndef BIGINT_HPP_
#define BIGINT_HPP_

#include <fstream>
#include <memory>
#include <math.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <utility>

class BigInt {
  private:
    char* number;

    size_t size;

    bool sign = true;

    void Resize(BigInt& temp, const size_t n) const;

    void ReduceZeros(BigInt& temp) const;

    void HelpMult(BigInt& temp, const BigInt& num1, const BigInt& num2) const;

    void HelpAdd(BigInt& temp, const BigInt& num1, const BigInt& num2) const;

    void HelpSub(BigInt& temp, const BigInt& num1, const BigInt& num2) const;

  public:
    BigInt(): number(nullptr),
               size(0),
               sign(true) {}

    BigInt(const std::string& input);

    BigInt(const int input);

    BigInt(const BigInt& input);

    BigInt(BigInt&& input);

    BigInt& operator= (const BigInt& other);

    BigInt& operator= (const int& other);

    BigInt& operator= (BigInt&& other);

    bool operator> (const BigInt& other) const;

    bool operator> (const int& other) const;

    bool operator== (const BigInt& other) const;

    bool operator!= (const BigInt& other) const { return (!(*this == other)); }

    bool operator!= (const int& other) const;

    bool operator>= (const BigInt& other) const
      { return (*this > other || *this == other); }

    bool operator>= (const int& other) const;

    bool operator<= (const BigInt& other) const { return (!(*this > other)); }

    bool operator<= (const int& other) const;

    bool operator< (const BigInt& other) const { return (!(*this >= other)); }

    bool operator< (const int& other) const;

    BigInt operator- () const;

    BigInt operator+ (const BigInt& other) const;

    BigInt operator+ (const int& other) const;

    BigInt operator- (const BigInt& other) const;

    BigInt operator- (const int& other) const;

    BigInt operator* (const BigInt& other) const;

    BigInt operator* (const int& other) const;

    BigInt operator*= (const BigInt &other);

    BigInt operator*= (const int& other);

    BigInt& operator+= (const BigInt& other);

    BigInt operator+= (const int& other);

    BigInt& operator-= (const BigInt& other);

    BigInt operator-= (const int& other);

    ~BigInt();

    size_t getSize() const { return size; }

    bool isNeg() const { return !sign; }

    bool isEmpty() const { return (number == nullptr && sign && size == 0); }

    char getDigit(size_t i) const { return number[i]; }

    friend std::ostream& operator<< (std::ostream& out, const BigInt& num);

    friend std::ofstream& operator<< (std::ofstream& out, const BigInt& num);
};

#endif  // BIGINT_HPP_
