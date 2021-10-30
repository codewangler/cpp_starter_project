// @file      sandbox.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021  Roger Davies, all rights reserved

#include "lib/toolbox.hpp"

int main() {

  rtb::Logger::LogError(0, "message");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkNull);
  rtb::Logger::LogError(1, "message");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::LogError(2, "message");

  rtb::Logger::SetFileSinkPath("foo.log");
  rtb::Logger::SetFileSinkPath("bar.log");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError(12.25F, "Float value");
  rtb::Logger::SetFileSinkPath("yalf.log");
  rtb::Logger::LogError(12, "int value");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::LogError("This goes to cout");
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError("This goes to yalf.log");

  return EXIT_SUCCESS;
}