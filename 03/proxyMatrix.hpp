#ifndef PROXY_MATRIX_HPP_
#define PROXY_MATRIX_HPP_

#include <cstddef>
#include <stdexcept>

class ProxyMatrix {
  private:
    size_t rowNumber;
    int*   row;

  public:
    ProxyMatrix():
    rowNumber(0),
    row(nullptr) {}

  ProxyMatrix(size_t n);

  void newElement(size_t n);

  void delElement();

  ~ProxyMatrix() {}

  int& operator[] (size_t n) const;

  int& operator[] (size_t n);

};


#endif  // PROXY_MATRIX_HPP_
