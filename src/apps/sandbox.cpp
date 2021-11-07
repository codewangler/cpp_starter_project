// @file      sandbox.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021  Roger Davies, all rights reserved

#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "lib/toolbox.hpp"

#define PROFILING 1

//  Useful macros for using the Instrumentor profiler.
#if PROFILING
#define PROFILE_SCOPE(name) rtb::InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

void PrintFunction() {
  PROFILE_FUNCTION();
  for (int i = 0; i < 10000; i++) {
    std::cout << "Hello World #" << i << std::endl;
  }
}

void PrintFunction(int j) {
  PROFILE_FUNCTION();
  for (int i = 0; i < 10000; i++) {
    std::cout << "Hello World #" << sqrt(i + j) << std::endl;
  }
}

void RunBenchmarks() {
  PROFILE_FUNCTION();
  std::cout << "Running benchmarks...\n";

  std::thread a([](){PrintFunction(2);});
  PrintFunction();
  a.join();
}

int main() {
  /* rtb::Timer t;
  rtb::Timer t2("t2");
  rtb::Timer t3("t3");

  rtb::Logger::LogError(99);
  rtb::Logger::LogError(0, "message");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkNull);
  rtb::Logger::LogError(1, "message");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::LogError(2, "message");

  t3.Mark();

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
  rtb::Logger::LogInfo(222, "Info"); */

  rtb::Instrumentor::GetInstance().BeginSession("Profile");
  RunBenchmarks();
  rtb::Instrumentor::GetInstance().EndSession();

  return EXIT_SUCCESS;
}