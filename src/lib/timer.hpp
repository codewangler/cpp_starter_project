// @file      timer.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#pragma once

#include <chrono>
#include <string>

namespace rtb {
class Timer {
 public:
  explicit Timer(std::string tag = "");
  Timer(const Timer &rhs) = delete;
  Timer& operator=(const Timer &) = delete;
  Timer(const Timer &&rhs) = delete;
  Timer& operator=(const Timer &&) = delete;
  ~Timer();

  void Reset();
  void Mark();
  double ElapsedTime();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point_;
  std::string tag_;
};
}  // namespace rtb