// @file      sandbox.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021  Roger Davies, all rights reserved

#include <chrono>
#include <iomanip>
#include <sstream>

#include "lib/toolbox.hpp"

int main() {
  /* auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  rtb::Logger::LogInfo(ss.str()); */

  rtb::Timer t;
  rtb::Timer t2("t2");

  rtb::Logger::LogError(99);
  rtb::Logger::LogError(0, "message");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkNull);
  rtb::Logger::LogError(1, "message");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::LogError(2, "message");

  rtb::Logger::SetFileSinkPath("foo.log");
  rtb::Logger::SetFileSinkPath("bar.log");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError(12.25F, "Float value");
  rtb::Logger::SetFileSinkPath("./log/yalf.log");
  rtb::Logger::LogError(12, "int value");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::LogError("This goes to cout");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError("This goes to yalf.log");
  rtb::Logger::LogWarning(99, "Danger!");
  rtb::Logger::LogInfo(222, "Info");


  return EXIT_SUCCESS;
}