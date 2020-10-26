#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include "proxyMatrix.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>

class Matrix {
  private:
    size_t        rows;
    size_t        cols;
    ProxyMatrix*  matrix;

  public:
    Matrix(size_t n, size_t m);

    Matrix(const Matrix& matr);

    ~Matrix();

    size_t getRows() const { return rows; }

    size_t getColumns() const { return cols; }

    ProxyMatrix& operator[] (size_t n) const;

    ProxyMatrix& operator[] (size_t n);

    bool operator== (const Matrix& matr) const;

    bool operator!= (const Matrix& matr) const { return !(*this == matr); }

    Matrix& operator= (const Matrix& matr);

    Matrix operator+ (const Matrix& matr) const;

    Matrix& operator*= (const int a);

    friend std::ostream& operator<< (std::ostream &out, const Matrix &matr);
    friend std::ofstream& operator<< (std::ofstream &out, const Matrix &matr);
};

#endif  // MATRIX_HPP_
