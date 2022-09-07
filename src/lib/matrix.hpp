// @file      matrix.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2022 Roger Davies, all rights reserved

#pragma once

#include <cstddef>
#include <vector>

namespace rtb {
/**
 * @brief A class that represents a matrix of real numbers.
 *
 */
class Matrix {
 public:
  Matrix(size_t rows, size_t cols);
  double& operator()(size_t i, size_t j);
  double operator()(size_t i, size_t j) const;
  [[nodiscard]] size_t Rows() const { return rows_; }
  [[nodiscard]] size_t Cols() const { return cols_; }
  [[nodiscard]] bool IsRowVector() const { return rows_ == 1; }
  [[nodiscard]] bool IsColVector() const { return cols_ == 1; }
  [[nodiscard]] bool IsSquare() const { return rows_ != 0 && rows_ == cols_; }

 private:
  size_t rows_;
  size_t cols_;
  std::vector<double> elements_;
};
}  // namespace rtb