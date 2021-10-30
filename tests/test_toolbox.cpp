// @file      test_toolbox.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved
#include <gtest/gtest.h>

#include <filesystem>

#include "lib/toolbox.hpp"

struct Loggable {
  Loggable(std::string str, const int i) : str_(std::move(str)), i_(i) {}
  std::string str_;
  int i_;
};

std::ostream &operator<<(std::ostream &os, const Loggable &object) {
  os << object.str_ << ": " << object.i_;
  return os;
}

TEST(TestLogger, LogErrorInt) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogError(10);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Error] 10\n", output.c_str());
}

TEST(TestLogger, LogErrorIntWithMessage) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogError(10, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Error] Message: 10\n", output.c_str());
}

TEST(TestLogger, LogErrorLoggableType) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogError(l);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Error] loggable type: 666\n", output.c_str());
}

TEST(TestLogger, LogErrorLoggableTypeWithMessage) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogError(l, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Error] Message: loggable type: 666\n", output.c_str());
}

TEST(TestLogger, LogWarningInt) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogWarning(10);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Warning] 10\n", output.c_str());
}

TEST(TestLogger, LogWarningIntWithMessage) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogWarning(10, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Warning] Message: 10\n", output.c_str());
}

TEST(TestLogger, LogWarningLoggableType) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogWarning(l);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Warning] loggable type: 666\n", output.c_str());
}

TEST(TestLogger, LogWarningLoggableTypeWithMessage) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogWarning(l, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("[Warning] Message: loggable type: 666\n", output.c_str());
}

TEST(TestLogger, LogInfoInt) {
  testing::internal::CaptureStdout();
  rtb::Logger::LogInfo(10);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_STREQ("[Info] 10\n", output.c_str());
}

TEST(TestLogger, LogInfoIntWithMessage) {
  testing::internal::CaptureStdout();
  rtb::Logger::LogInfo(10, "Message");
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_STREQ("[Info] Message: 10\n", output.c_str());
}

TEST(TestLogger, LogInfoLoggableType) {
  testing::internal::CaptureStdout();
  Loggable l("loggable type", 666);
  rtb::Logger::LogInfo(l);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_STREQ("[Info] loggable type: 666\n", output.c_str());
}

TEST(TestLogger, LogInfoLoggableTypeWithMessage) {
  testing::internal::CaptureStdout();
  Loggable l("loggable type", 666);
  rtb::Logger::LogInfo(l, "Message");
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_STREQ("[Info] Message: loggable type: 666\n", output.c_str());
}

TEST(TestLogger, SetSinkCout) {
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  testing::internal::CaptureStdout();
  rtb::Logger::LogError(10);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_STREQ("[Error] 10\n", output.c_str());
}

TEST(TestLogger, SetSinkNull) {
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkNull);
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();
  rtb::Logger::LogError(10);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_STREQ("", output.c_str());
  output = testing::internal::GetCapturedStderr();
  ASSERT_STREQ("", output.c_str());
}

TEST(TestLogger, LogToDefaultFile) {
  const std::string log_filename("rtb.log");
  if (std::filesystem::exists(log_filename)) {
    std::filesystem::remove(log_filename);
  }

  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError("Error!");

  ASSERT_TRUE(std::filesystem::exists(log_filename));
}

TEST(TestLogger, ChangeLogFile) {
  const std::string log_filename("test.log");
  if (std::filesystem::exists(log_filename)) {
    std::filesystem::remove(log_filename);
  }

  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::SetFileSinkPath(log_filename);
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError("Error");

  ASSERT_TRUE(std::filesystem::exists(log_filename));
}

TEST(TestLogger, ChangeLogFile2) {
  const std::string log_filename("test1.log");
  if (std::filesystem::exists(log_filename)) {
    std::filesystem::remove(log_filename);
  }
  const std::string log_filename2("test2.log");
  if (std::filesystem::exists(log_filename2)) {
    std::filesystem::remove(log_filename2);
  }

  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  rtb::Logger::SetFileSinkPath(log_filename);
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkFile);
  rtb::Logger::LogError("Error1");
  rtb::Logger::SetFileSinkPath(log_filename2);
  rtb::Logger::LogError("Error2");

  ASSERT_TRUE(std::filesystem::exists(log_filename));
  ASSERT_TRUE(std::filesystem::exists(log_filename2));
}