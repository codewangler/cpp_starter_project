// @file      timer.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "timer.hpp"

#include <iostream>
#include <sstream>

#include "logger.hpp"

namespace rtb {
Timer::Timer(std::string tag) : tag_(std::move(tag)) {
  start_time_point_ = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() { Stop(); }

void Timer::Stop() {
  auto stop_time_point = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration =
      stop_time_point - start_time_point_;
  std::ostringstream ss;
  ss << duration.count() << "ms";
  if (tag_.empty()) {
    rtb::Logger::LogInfo(ss.str());
  } else {
    rtb::Logger::LogInfo(ss.str(), tag_);
  }
}
}  // namespace rtb