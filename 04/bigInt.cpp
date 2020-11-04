#include "bigInt.hpp"

void BigInt::Resize(BigInt& temp, const size_t n) const {
  temp.size = n - 1;
  if (temp.number != nullptr)
    delete [] temp.number;
  temp.number = new char[n];
}

void BigInt::ReduceZeros(BigInt& temp) const {
  size_t i = temp.size;
  while ((i > 0) && (temp.number[i - 1] == '0')) {
    temp.size--;
    i--;
  }
  if (i == 0) {
    temp.sign = true;
    temp.size = 1;
    temp.number[0] = '0';
  }
}

void BigInt::HelpMult(BigInt& temp, const BigInt& num1,
                      const BigInt& num2) const {
  int temp1, temp2 = 0;
  for (size_t i = 0; i < num2.size; i++) {
    for (size_t j = 0; j < num1.size; j++) {
      temp1 = (num1.number[j] - '0') * (num2.number[i] - '0')
              + temp2 + (temp.number[i + j] - '0');
      temp2 = 0;
      if (temp1 >= 10) {
        temp2 = temp1 / 10;
      }
      temp.number[i + j] = char (temp1 % 10 + '0');
    }
    if (temp2 > 0) {
      temp.number[i + num1.size] = char (temp2 + '0');
    }
    temp2 = 0;
  }
}

void BigInt::HelpAdd(BigInt& temp, const BigInt& num1,
                     const BigInt& num2) const {
  int temp1 = 0;
  int temp2 = 0;
  for (size_t i = 0; i < num2.size; i++) {
    temp1 = num1.number[i] + num2.number[i] + temp2 - '0' - '0';
    temp2 = 0;
    if (temp1 >= 10) {
      temp2 = 1;
    }
    temp.number[i] = char (temp1 % 10 + '0');
  }
  for (size_t i = num2.size; i < num1.size ; i++) {
    temp1 = num1.number[i] + temp2  - '0';
    temp2 = 0;
    if (temp1 >= 10) {
      temp2 = 1;
    }
    temp.number[i] = char (temp1 % 10 + '0');
  }
  if (temp2 != 0) {
    temp.size++;
    temp.number[temp.size - 1] = '1';
  }
}

void BigInt::HelpSub(BigInt& temp, const BigInt& num1,
                     const BigInt& num2) const {
  int temp1 = 0;
  int temp2 = 0;
  for (size_t i = 0; i < num2.size; i++) {
    temp1 = (num1.number[i] - num2.number[i] - temp2);
    temp2 = 0;
    if (temp1 < 0) {
      temp2 = 1;
      temp.number[i] = char ((10 + temp1) % 10 + int('0'));
    }
    if (temp1 >= 0) {
      temp.number[i] = char ((temp1) % 10 + int('0'));
    }
  }
  for (size_t i = num2.size; i < num1.size; i++) {
    temp1 = (num1.number[i] - temp2  - '0');
    temp2 = 0;
    if (temp1 < 0) {
      temp2 = 1;
      temp.number[i] = char ((10 + temp1) % 10 + int('0'));
    }
    if (temp1 >= 0) {
      temp.number[i] = char ((temp1) % 10 + int('0'));
    }
  }
  if (temp2 != 0) {
    temp1 = (num1.number[size - 1] - temp2  - '0');
    temp.number[size - 1] = char(temp1 % 10 + '0');
  }
}

BigInt::BigInt (const std::string& input) {
  size_t t = 0;
  if (input[0] == '-') {
    t++;
    sign = false;
  }
  size = input.size() - t;
  number = new char[size];
  for (size_t i = input.size(); i > t; i--) {
     if (isdigit(input[i - 1])) {
       number[size - i + t] = input[i - 1];
     } else {
      delete [] number;
      throw "Not valid input string";
    }
  }
}

BigInt::BigInt (const int input) {
  int temp = input;
  int t = 1;
  sign = (temp < 0 ? false: true);
  temp = abs(temp);
  while (temp / 10 != 0) {
    t++;
    temp = temp / 10;
  }
  number = new char[t];
  size = t;
  temp = abs(input);
  for (size_t i = t; i > 0; i--) {
    number[size - i] = char(temp % 10 + '0');
    temp = temp / 10;
  }
}

BigInt::BigInt (const BigInt& input) {
  this->number = nullptr;
  *this = input;
}

BigInt::BigInt (BigInt&& input) {
  number = input.number;
  size = input.size;
  sign = input.sign;
  input.number = nullptr;
  input.size = 0;
  input.sign = true;
}

BigInt& BigInt::operator= (const BigInt& other) {
  if (this == &other)
    return *this;
  size = other.size;
  if (number != nullptr) {
    delete [] number;
  }
  number = new char[other.size];
  sign = other.sign;
  for (size_t i = 0; i < size; i++)
    number[i] = other.number[i];
  return *this;
}

BigInt& BigInt::operator= (const int& other) {
  BigInt temp(other);
  *this = temp;
  return *this;
}

BigInt& BigInt::operator= (BigInt&& other) {
  if (this == &other)
    return *this;
  if (number != nullptr)
    delete [] number;
  size = other.size;
  number = other.number;
  sign = other.sign;
  other.number = nullptr;
  other.sign = true;
  other.size = 0;
  return *this;
}

bool BigInt::operator> (const BigInt& other) const {
  if (this->size > other.size)
    return true;
  else
    if (this->size < other.size)
      return false;
  for (size_t i = this->size; i >= 1; i--) {
    if (this->number[i - 1] > other.number[i - 1])
      return true;
    if (this->number[i - 1] < other.number[i - 1])
      return false;
  }
  return false;
}

bool BigInt::operator> (const int& other) const {
  BigInt temp(other);
  return *this > temp;
}

bool BigInt::operator== (const BigInt& other) const {
  if (this->size != other.size)
    return false;
  for (size_t i = this->size; i > 0; i--)
    if (this->number[i - 1] != other.number[i - 1])
      return false;
  return true;
}

BigInt BigInt::operator+ (const BigInt& other) const {
  BigInt temp;
  size_t t0 = std::max(this->size, other.size) + 1;
  Resize(temp, t0);
  if (other >= *this) {
    if ((other.sign && this->sign) || !(other.sign || this->sign)) {
      temp.sign = other.sign;
      HelpAdd(temp, other, *this);
    } else {
      temp.sign = (other.sign && !this->sign);
      HelpSub(temp, other, *this);
    }
  } else {
    if ((other.sign && this->sign) || !(other.sign || this->sign)) {
      temp.sign = other.sign;
      HelpAdd(temp, *this, other);
    } else {
      temp.sign = (this->sign && !other.sign);
      HelpSub(temp, *this, other);
    }
  }
  ReduceZeros(temp);
  return temp;
}

bool BigInt::operator!= (const int& other) const {
  BigInt temp(other);
  return *this != temp;
}

bool BigInt::operator>= (const int& other) const {
  BigInt temp(other);
  return *this >= temp;
}

bool BigInt::operator<= (const int& other) const {
  BigInt temp(other);
  return *this <= temp;
}


BigInt BigInt::operator+ (const int& other) const {
  BigInt temp(other);
  return *this + temp;
}

bool BigInt::operator< (const int& other) const {
  BigInt temp(other);
  return *this < temp;
}

BigInt BigInt::operator- () const {
  BigInt temp(*this);
  temp.sign = !temp.sign;
  return temp;
}

BigInt BigInt::operator- (const BigInt& other) const {
  BigInt temp = other;
  return *this + (-temp);
}

BigInt BigInt::operator- (const int& other) const {
  BigInt temp(other);
  return *this - temp;
}

BigInt BigInt::operator* (const BigInt& other) const {
  BigInt temp;
  size_t t0 = this->size + other.size + 1;
  Resize(temp, t0);
  for (size_t i = 0; i < temp.size; i++)
    temp.number[i] = '0';
  if (other >= *this) {
    HelpMult(temp, other, *this);
  } else {
    HelpMult(temp, *this, other);
  }
  ReduceZeros(temp);
  return temp;
}

BigInt BigInt::operator* (const int& other) const {
  BigInt temp(other);
  return (*this) * temp;
}

BigInt BigInt::operator*= (const BigInt &other) {
  *this = other * (*this);
  return *this;
}

BigInt BigInt::operator*= (const int& other) {
  BigInt temp(other);
  *this *= temp;
  return (*this);
}

BigInt& BigInt::operator+= (const BigInt& other) {
  *this = *this + other;
  return *this;
}

BigInt BigInt::operator+= (const int& other)  {
  BigInt temp(other);
  *this += temp;
  return (*this);
}

BigInt& BigInt::operator-= (const BigInt& other) {
  *this = *this - other;
  return *this;
}

BigInt BigInt::operator-= (const int& other) {
  BigInt temp(other);
  *this -= temp;
  return (*this);
}

BigInt::~BigInt () {
  if (number != nullptr)
    delete [] number;
  size = 0;
  sign = true;
}


std::ostream& operator<< (std::ostream& out, const BigInt& num) {
  if (num.isNeg()) {
    out << '-';
  }
  for (size_t i = num.getSize(); i > 0; i--) {
      out << num.getDigit(i - 1);
  }
  return out;
}

std::ofstream& operator<< (std::ofstream& out, const BigInt& num) {
  char *t = new char[1];
  if (num.isNeg()) {
    t[0] = '-';
    out.write(t, 1);
  }
  for (size_t i = num.getSize(); i > 0; i--) {
    t[0] = num.getDigit(i - 1);
    out.write(t, 1);
  }
  delete [] t;
  return out;
}
