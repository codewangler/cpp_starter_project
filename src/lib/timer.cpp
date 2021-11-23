// @file      timer.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "timer.hpp"

#include <iostream>
#include <sstream>

#include "logger.hpp"

namespace rtb {
Timer::Timer(std::string tag) : tag_(std::move(tag)) { Reset(); }

Timer::~Timer() { Mark(); }

void Timer::Reset() {
  start_time_point_ = std::chrono::high_resolution_clock::now();
}

void Timer::Mark() {
  auto stop_time_point = std::chrono::high_resolution_clock::now();
  auto start =
      std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point_)
          .time_since_epoch()
          .count();
  auto stop =
      std::chrono::time_point_cast<std::chrono::microseconds>(stop_time_point)
          .time_since_epoch()
          .count();
  auto duration = stop - start;
  auto micro_seconds = static_cast<double>(duration);

  std::ostringstream ss;
  ss << micro_seconds * 0.001 << "ms";
  if (tag_.empty()) {
    rtb::Logger::LogInfo(ss.str());
  } else {
    rtb::Logger::LogInfo(ss.str(), tag_);
  }
}

double Timer::ElapsedTime() {
  auto stop_time_point = std::chrono::high_resolution_clock::now();
  auto start =
      std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point_)
          .time_since_epoch()
          .count();
  auto stop =
      std::chrono::time_point_cast<std::chrono::microseconds>(stop_time_point)
          .time_since_epoch()
          .count();
  auto duration = stop - start;
  auto micro_seconds = static_cast<double>(duration);

  return micro_seconds;
}
}  // namespace rtb