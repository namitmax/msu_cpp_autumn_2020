#include "matrix.hpp"

Matrix::Matrix(size_t n, size_t m):
  rows(n),
  cols(m) {
  if ((n == 0) || (m == 0)) {
    throw std::out_of_range("Number of rows or columns is 0.");
  }
  matrix = new ProxyMatrix[n];
  for (size_t i = 0; i < n; i++)
    matrix[i].newElement(m);
}

Matrix::Matrix(const Matrix& matr) {
  *this = matr;
}

Matrix::~Matrix() {
  if (matrix != nullptr) {
    for (size_t i = 0; i < rows; i++)
      matrix[i].delElement();
    delete [] matrix;
  }
}

ProxyMatrix& Matrix::operator[] (size_t n) const {
  if (n >= rows) {
    throw std::out_of_range("col index is out of range");
  }
  return matrix[n];
}

ProxyMatrix& Matrix::operator[] (size_t n) {
  if (n >= rows) {
    throw std::out_of_range("col index is out of range");
  }
  return matrix[n];
}

bool Matrix::operator== (const Matrix& matr) const {
  if ((cols != matr.getColumns()) || (rows != matr.getRows())) {
    return false;
  }
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      if (matrix[i][j] != matr[i][j])
        return false;
  return true;
}

Matrix& Matrix::operator= (const Matrix& matr) {
  if ((cols != matr.getColumns()) || (rows != matr.getRows())) {
    if (matrix != nullptr) {
      for (size_t i = 0; i < rows; i++)
        matrix[i].delElement();
      delete [] matrix;
    }
    rows = matr.getRows();
    cols = matr.getColumns();
    matrix = new ProxyMatrix[rows];
    for (size_t i = 0; i < rows; i++)
      matrix[i].newElement(cols);
  }
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      matrix[i][j] = matr[i][j];
  return *this;
}

Matrix Matrix::operator+ (const Matrix& matr) const {
  if ((cols != matr.getColumns()) || (rows != matr.getRows())) {
    throw std::out_of_range("index is out of range");
  }
  Matrix result(rows, cols);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
  result[i][j] = matrix[i][j] + matr[i][j];
  return result;
}

Matrix& Matrix::operator*= (const int a) {
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      matrix[i][j] *= a;
  return *this;
}

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
