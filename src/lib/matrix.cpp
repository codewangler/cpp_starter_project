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
}  // namespace rtb
