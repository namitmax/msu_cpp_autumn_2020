#include "proxyMatrix.hpp"

ProxyMatrix::ProxyMatrix(size_t n):
  rowNumber(n) {
  row = new int[n];
}

void ProxyMatrix::newElement(size_t n) {
  rowNumber = n;
  row = new int[n];
}

void ProxyMatrix::delElement() {
  if (row != nullptr)
    delete [] row;
}

int& ProxyMatrix::operator[] (size_t n) const {
  if (n >= rowNumber) {
    throw std::out_of_range("row index is out of range");
  }
  return row[n];
}

int& ProxyMatrix::operator[] (size_t n) {
  if (n >= rowNumber) {
    throw std::out_of_range("row index is out of range");
  }
  return row[n];
}
