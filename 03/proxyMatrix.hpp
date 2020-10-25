#ifndef PROXY_MATRIX_HPP_
#define PROXY_MATRIX_HPP_

class proxyMatrix {
  private:
    size_t rowNumber;
    int*   row;

  public:
    proxyMatrix():
    rowNumber(0),
    row(nullptr) {}

  proxyMatrix(size_t n):
    rowNumber(n) {
    row = new int[n];
  }

  void newElement(size_t n) {
    rowNumber = n;
    row = new int[n];
  }

  void delElement() {
    if (row != nullptr)
      delete [] row;
  }

  ~proxyMatrix() {}

  int operator[] (size_t n) const {
    if (n >= rowNumber) {
      throw std::out_of_range("row index is out of range");
    }
    return row[n];
  }

  int& operator[] (size_t n) {
    if (n >= rowNumber) {
      throw std::out_of_range("row index is out of range");
    }
    return row[n];
  }
};


#endif  // PROXY_MATRIX_HPP_
