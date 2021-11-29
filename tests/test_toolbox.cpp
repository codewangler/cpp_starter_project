// @file      test_toolbox.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <thread>

#include "lib/toolbox.hpp"

struct Loggable {
  Loggable(std::string str, const int i) : str_(std::move(str)), i_(i) {}
  std::string str_;
  int i_;
};

std::ostream& operator<<(std::ostream& os, const Loggable& object) {
  os << object.str_ << ": " << object.i_;
  return os;
}

/* TEST(TestLogger, LogErrorInt) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogError(10);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Error"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
}

TEST(TestLogger, LogErrorIntWithMessage) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogError(10, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Error"));
  ASSERT_THAT(output, testing::HasSubstr("Message"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
}

TEST(TestLogger, LogErrorLoggableType) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogError(l);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Error"));
  ASSERT_THAT(output, testing::HasSubstr("loggable type"));
  ASSERT_THAT(output, testing::HasSubstr("666"));
}

TEST(TestLogger, LogErrorLoggableTypeWithMessage) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogError(l, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Error"));
  ASSERT_THAT(output, testing::HasSubstr("Message"));
  ASSERT_THAT(output, testing::HasSubstr("loggable type"));
  ASSERT_THAT(output, testing::HasSubstr("666"));
}

TEST(TestLogger, LogWarningInt) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogWarning(10);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Warning"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
}

TEST(TestLogger, LogWarningIntWithMessage) {
  testing::internal::CaptureStderr();
  rtb::Logger::LogWarning(10, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Warning"));
  ASSERT_THAT(output, testing::HasSubstr("Message"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
}

TEST(TestLogger, LogWarningLoggableType) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogWarning(l);
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Warning"));
  ASSERT_THAT(output, testing::HasSubstr("loggable type"));
  ASSERT_THAT(output, testing::HasSubstr("666"));
}

TEST(TestLogger, LogWarningLoggableTypeWithMessage) {
  testing::internal::CaptureStderr();
  Loggable l("loggable type", 666);
  rtb::Logger::LogWarning(l, "Message");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_THAT(output, testing::HasSubstr("Warning"));
  ASSERT_THAT(output, testing::HasSubstr("Message"));
  ASSERT_THAT(output, testing::HasSubstr("loggable type"));
  ASSERT_THAT(output, testing::HasSubstr("666"));
}

TEST(TestLogger, LogInfoInt) {
  testing::internal::CaptureStdout();
  rtb::Logger::LogInfo(10);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_THAT(output, testing::HasSubstr("Info"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
}

TEST(TestLogger, LogInfoIntWithMessage) {
  testing::internal::CaptureStdout();
  rtb::Logger::LogInfo(10, "Message");
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_THAT(output, testing::HasSubstr("Info"));
  ASSERT_THAT(output, testing::HasSubstr("Message"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
}

TEST(TestLogger, LogInfoLoggableType) {
  testing::internal::CaptureStdout();
  Loggable l("loggable type", 666);
  rtb::Logger::LogInfo(l);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_THAT(output, testing::HasSubstr("Info"));
  ASSERT_THAT(output, testing::HasSubstr("loggable type"));
  ASSERT_THAT(output, testing::HasSubstr("666"));
}

TEST(TestLogger, LogInfoLoggableTypeWithMessage) {
  testing::internal::CaptureStdout();
  Loggable l("loggable type", 666);
  rtb::Logger::LogInfo(l, "Message");
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_THAT(output, testing::HasSubstr("Info"));
  ASSERT_THAT(output, testing::HasSubstr("Message"));
  ASSERT_THAT(output, testing::HasSubstr("loggable type"));
  ASSERT_THAT(output, testing::HasSubstr("666"));
}

TEST(TestLogger, SetSinkCout) {
  rtb::Logger::SetErrorSink(rtb::Logger::kSinkCout);
  testing::internal::CaptureStdout();
  rtb::Logger::LogError(10);
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_THAT(output, testing::HasSubstr("Error"));
  ASSERT_THAT(output, testing::HasSubstr("10"));
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
  const std::string log_filename("./log/test.log");
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
  const std::string log_filename("./log/test1.log");
  if (std::filesystem::exists(log_filename)) {
    std::filesystem::remove(log_filename);
  }
  const std::string log_filename2("./log/test2.log");
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
TEST(TestTimer, TimerTagged) {
  using namespace std::literals::chrono_literals;
  rtb::Timer t("t1");
  std::this_thread::sleep_for(1s);
  testing::internal::CaptureStdout();
  t.Mark();
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_THAT(output, testing::HasSubstr("t1"));
  ASSERT_THAT(output, testing::HasSubstr("ms"));
} */

TEST(TestClargParser, AddFlag) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddFlagToSearchList("b");
  parser->AddFlagToSearchList("v");
  ASSERT_TRUE(parser->GetFlagSearchListCount() == 2);
}

TEST(TestClargParser, AddDuplicateFlag) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddFlagToSearchList("b");
  parser->AddFlagToSearchList("v");
  parser->AddFlagToSearchList("b");
  ASSERT_TRUE(parser->GetFlagSearchListCount() == 2);
}

TEST(TestClargParser, ParseFoundFlag) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddFlagToSearchList("b");
  parser->AddFlagToSearchList("v");

  char first[]{"app name"};
  char second[]{"-b"};
  char third[]{"-d"};
  char* argv[3] {first, second, third};

  parser->Parse(3, argv);

  rtb::ClargFlag* flag_ptr = parser->GetFlag("b");
  ASSERT_TRUE(flag_ptr != nullptr);
  ASSERT_TRUE(flag_ptr->found());
  ASSERT_TRUE(flag_ptr->value());
}

TEST(TestClargParser, ParseNotFoundFlag) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddFlagToSearchList("b");
  parser->AddFlagToSearchList("v");

  char first[]{"app name"};
  char second[]{"-b"};
  char third[]{"-d"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargFlag* flag_ptr = parser->GetFlag("v");
  ASSERT_TRUE(flag_ptr != nullptr);
  ASSERT_FALSE(flag_ptr->found());
  ASSERT_FALSE(flag_ptr->value());
}

TEST(TestClargParser, ParseFlagNotInSearchList) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddFlagToSearchList("b");
  parser->AddFlagToSearchList("v");

  char first[]{"app name"};
  char second[]{"-b"};
  char third[]{"-d"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargFlag* flag_ptr = parser->GetFlag("d");
  ASSERT_TRUE(flag_ptr == nullptr);
}

TEST(TestClargParser, AddParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width");
  parser->AddParamToSearchList("height");
  ASSERT_TRUE(parser->GetParamSearchListCount() == 2);
}

TEST(TestClargParser, AddDuplicateParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width");
  parser->AddParamToSearchList("height");
  parser->AddParamToSearchList("width");
  ASSERT_TRUE(parser->GetParamSearchListCount() == 2);
}

TEST(TestClargParser, ParseFoundParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width");
  parser->AddParamToSearchList("height");

  char first[]{"app name"};
  char second[]{"-width=500"};
  char third[]{"-height=600"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargParam* flag_ptr = parser->GetParam("width");
  ASSERT_TRUE(flag_ptr != nullptr);
  ASSERT_TRUE(flag_ptr->found());
  ASSERT_STREQ(flag_ptr->value().c_str(), "500");
}

TEST(TestClargParser, ParseNotFoundParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width");
  parser->AddParamToSearchList("height");
  parser->AddParamToSearchList("size");

  char first[]{"app name"};
  char second[]{"-width=500"};
  char third[]{"-height=600"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargParam* flag_ptr = parser->GetParam("size");
  ASSERT_TRUE(flag_ptr != nullptr);
  ASSERT_FALSE(flag_ptr->found());
  ASSERT_STREQ(flag_ptr->value().c_str(), "");
}

TEST(TestClargParser, ParseParamNotInSearchList) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width");
  parser->AddParamToSearchList("height");
  parser->AddParamToSearchList("size");

  char first[]{"app name"};
  char second[]{"-width=500"};
  char third[]{"-height=600"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargParam* flag_ptr = parser->GetParam("xpto");
  ASSERT_TRUE(flag_ptr == nullptr);
}