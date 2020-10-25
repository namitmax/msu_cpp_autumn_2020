#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include "proxyMatrix.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>

class Matrix {
  private:
    size_t        rows;
    size_t        cols;
    proxyMatrix*  matrix;

  public:
    Matrix(size_t n, size_t m):
      rows(n),
      cols(m) {
      if ((n == 0) || (m == 0)) {
        throw std::out_of_range("Number of rows or columns is 0.");
      }
      matrix = new proxyMatrix[n];
      for (size_t i = 0; i < n; i++)
        matrix[i].newElement(m);
    }

    Matrix(const Matrix& matr) {
      *this = matr;
    }

    ~Matrix() {
      if (matrix != nullptr) {
        for (size_t i = 0; i < rows; i++)
          matrix[i].delElement();
        delete [] matrix;
      }
    }

    size_t getRows() const {
      return rows;
    }

    size_t getColumns() const {
      return cols;
    }

    proxyMatrix operator[] (size_t n) const {
      if (n >= rows) {
        throw std::out_of_range("col index is out of range");
      }
      return matrix[n];
    }

    proxyMatrix& operator[] (size_t n) {
      if (n >= rows) {
        throw std::out_of_range("col index is out of range");
      }
      return matrix[n];
    }

    bool operator== (const Matrix& matr) const {
      if ((cols != matr.getColumns()) || (rows != matr.getRows())) {
        return false;
      }
      for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
          if (matrix[i][j] != matr[i][j])
            return false;
      return true;
    }

    bool operator!= (const Matrix& matr) const {
      return !(*this == matr);
    }

    Matrix& operator= (const Matrix& matr) {
      if ((cols != matr.getColumns()) || (rows != matr.getRows())) {
        throw std::out_of_range("index is out of range");
      }
      for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
          matrix[i][j] = matr[i][j];
      return *this;
    }

    Matrix operator+ (const Matrix& matr) const {
      if ((cols != matr.getColumns()) || (rows != matr.getRows())) {
        throw std::out_of_range("index is out of range");
      }
      Matrix result(rows, cols);
      for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
          result[i][j] = matrix[i][j] + matr[i][j];
      return result;
    }

    Matrix& operator*= (const int a) {
      for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
          matrix[i][j] *= a;
      return *this;
    }

    friend std::ostream& operator<< (std::ostream &out, const Matrix &matr);
    friend std::ofstream& operator<< (std::ofstream &out, const Matrix &matr);
};

std::ofstream& operator<< (std::ofstream &out, const Matrix &matr) {
  for (size_t i = 0; i < matr.getRows(); i++) {
    for (size_t j = 0; j < matr.getColumns(); j++)
     out << matr[i][j] << " ";
    out << "\n";
  }
  return out;
}

std::ostream& operator<< (std::ostream &out, const Matrix &matr) {
  out << "\n";
  for (size_t i = 0; i < matr.getRows(); i++) {
    for (size_t j = 0; j < matr.getColumns(); j++)
     out << matr[i][j] << " ";
    out << "\n";
  }
  out << "\n";
  return out;
}

#endif  // MATRIX_HPP_
