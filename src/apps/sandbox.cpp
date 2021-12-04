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

  std::thread a([]() { PrintFunction(2); });
  PrintFunction();
  a.join();
}

int main(int argc, char* argv[]) {
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

  /* rtb::Instrumentor::GetInstance().BeginSession("Profile");
  RunBenchmarks();
  rtb::Instrumentor::GetInstance().EndSession(); */

  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();

  parser->AddFlagToSearchList("debug");
  parser->AddParamToSearchList("size", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("angle", rtb::ClargParam::ParamType::kFloat);
  parser->AddParamToSearchList("filepath",
                               rtb::ClargParam::ParamType::kStdString);
  parser->Parse(argc, argv);

  auto* flag_ptr = parser->GetFlag("debug");
  if (flag_ptr != nullptr) {
    rtb::Logger::LogInfo(flag_ptr->value(), flag_ptr->name());
  }

  auto* param_ptr = parser->GetParam("size");
  if (param_ptr != nullptr) {
    if (param_ptr->found()) {
      try {
        auto value = std::get<int>(param_ptr->value());
        rtb::Logger::LogInfo(value, param_ptr->name());
      } catch (...) {
        rtb::ClargParam::ErrorCode error =
            std::get<rtb::ClargParam::ErrorCode>(param_ptr->value());
        rtb::Logger::LogError(static_cast<int>(error), "Conversion error: size");
      }
    } else {
      rtb::Logger::LogInfo("Not in command line: size");
    }
  } else {
    rtb::Logger::LogError("size", "Not in search list");
  }

  param_ptr = parser->GetParam("angle");
  if (param_ptr != nullptr) {
    if (param_ptr->found()) {
      try {
        auto value = std::get<float>(param_ptr->value());
        rtb::Logger::LogInfo(value, param_ptr->name());
      } catch (...) {
        rtb::ClargParam::ErrorCode error =
            std::get<rtb::ClargParam::ErrorCode>(param_ptr->value());
        rtb::Logger::LogError(static_cast<int>(error),
                              "Conversion error: angle");
      }
    } else {
      rtb::Logger::LogInfo("Not in command line: angle");
    }
  } else {
    rtb::Logger::LogError("angle", "Not in search list");
  }

  param_ptr = parser->GetParam("filepath");
  if (param_ptr != nullptr) {
    if (param_ptr->found()) {
      try {
        auto value = std::get<std::string>(param_ptr->value());
        rtb::Logger::LogInfo(value, param_ptr->name());
      } catch (...) {
        rtb::ClargParam::ErrorCode error =
            std::get<rtb::ClargParam::ErrorCode>(param_ptr->value());
        rtb::Logger::LogError(static_cast<int>(error),
                              "Conversion error: filepath");
      }
    } else {
      rtb::Logger::LogInfo("Not in command line: filepath");
    }
  } else {
    rtb::Logger::LogError("filepath", "Not in search list");
  }

  rtb::Logger::LogError("Error text in red!");
  rtb::Logger::LogWarning("Warning text in yellow!");
  rtb::Logger::LogInfo("Info text in white!");

  return EXIT_SUCCESS;
}