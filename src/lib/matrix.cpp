// @file      matrix.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2022 Roger Davies, all rights reserved

#include "matrix.hpp"

#include <stdexcept>

namespace rtb {
/**
 * @brief Construct a new Matrix object.
 *
 * @param rows The number of rows.
 * @param cols The number of columns.
 */
Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), elements_(rows * cols) {}

/**
 * @brief Overload operator() to return a reference to an element of the array.
 *
 * @param i         The element row index.
 * @param j         The element column index.
 * @return double&  The reference to element [i, j].
 */
double& Matrix::operator()(size_t i, size_t j) {
  if (i >= rows_) {
    throw std::out_of_range("row");
  }
  if (j >= cols_) {
    throw std::out_of_range("column");
  }
  return elements_[i * cols_ + j];
}

/**
 * @brief Overload operator() to return the value of an element of the array.
 *
 * @param i         The element row index.
 * @param j         The element column index.
 * @return double   The value of element [i, j].
 */
double Matrix::operator()(size_t i, size_t j) const {
  return elements_[i * cols_ + j];
}

/**
 * @brief Overload operator+ to add a matrix to this one.
 *
 * @param other   The other matrix
 * @return Matrix The result
 */
Matrix Matrix::operator+(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Cannot add matrices of different size");
  }

  Matrix m(rows_, cols_);
  for (size_t k = 0; k < rows_ * cols_; k++) {
    m.elements_[k] = elements_[k] + other.elements_[k];
  }
  return m;
}

/**
 * @brief Overload operator- to subtract a matrix from this one.
 *
 * @param other   The other matrix
 * @return Matrix The result
 */
Matrix Matrix::operator-(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Cannot subtract matrices of different size");
  }

  Matrix m(rows_, cols_);
  for (size_t k = 0; k < rows_ * cols_; k++) {
    m.elements_[k] = elements_[k] - other.elements_[k];
  }
  return m;
}

/**
 * @brief Overload operator* to perform scalar multiplication.
 *
 * @param scalar   The multiplier
 * @return Matrix  The result
 */
Matrix Matrix::operator*(const double& scalar) const {
  Matrix m(rows_, cols_);
  for (size_t k = 0; k < rows_ * cols_; k++) {
    m.elements_[k] = elements_[k] * scalar;
  }
  return m;
}

/**
 * @brief Transpose this mxn matrix. The result is an nxm matrix whose first row
 * is the first column of this matrix etc.
 *
 * @return Matrix The transposed matrix.
 */
Matrix Matrix::Transpose() const {
  Matrix m(cols_, rows_);

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      m(j, i) = elements_[i * cols_ + j];
    }
  }

  return m;
}

/**
 * @brief Calculate the dot product of two matrices. The matrices must be
 * one-dimensional (either column or row vectors) and of the same size.
 *
 * @param other The other matrix.
 * @return      The dot product.
 */
double Matrix::DotProduct(const Matrix& other) const {
  if (!(rows_ == 1 || cols_ == 1)) {
    throw std::invalid_argument("This matrix is not one-dimensional");
  }
  if (!(other.rows_ == 1 || other.cols_ == 1)) {
    throw std::invalid_argument("The other matrix is not one-dimensional");
  }
  if (rows_ * cols_ != other.rows_ * other.cols_) {
    throw std::invalid_argument("The matrices are not the same size");
  }

  double dot_product = 0.0;

  for (size_t i = 0; i < rows_ * cols_; i++) {
    dot_product += elements_[i] * other.elements_[i];
  }

  return dot_product;
}

/**
 * @brief Multiply this matrix with another.
 * 
 * @param other   The other matrix
 * @return Matrix The result
 */
Matrix Matrix::Multiply(const Matrix& other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Number of rows in other matrix must equal the number of columns in "
        "this");
  }

  rtb::Matrix product(rows_, other.cols_);
  for (size_t i = 0; i < product.rows_; i++) {
    for (size_t j = 0; j < product.cols_; j++) {
      for (size_t k = 0; k < cols_; k++) {
        product(i, j) +=
            elements_[(i * cols_) + k] * other.elements_[j + (k * other.cols_)];
      }
    }
  }

  return product;
}
}  // namespace rtb
