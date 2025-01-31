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
}

TEST(TestClargParser, AddFlags) {
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
  char* argv[3]{first, second, third};

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

TEST(TestClargParser, AddParams) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("height", rtb::ClargParam::ParamType::kInt);
  ASSERT_TRUE(parser->GetParamSearchListCount() == 2);
}

TEST(TestClargParser, AddDuplicateParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("height", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);
  ASSERT_TRUE(parser->GetParamSearchListCount() == 2);
}

TEST(TestClargParser, ParseFoundParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("height", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-width=500"};
  char third[]{"-height=600"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargParam* flag_ptr = parser->GetParam("width");
  ASSERT_TRUE(flag_ptr != nullptr);
  ASSERT_TRUE(flag_ptr->found());
  ASSERT_STREQ(flag_ptr->raw_value().c_str(), "500");
}

TEST(TestClargParser, ParseNotFoundParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("height", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("size", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-width=500"};
  char third[]{"-height=600"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargParam* flag_ptr = parser->GetParam("size");
  ASSERT_TRUE(flag_ptr != nullptr);
  ASSERT_FALSE(flag_ptr->found());
  ASSERT_STREQ(flag_ptr->raw_value().c_str(), "");
}

TEST(TestClargParser, ParseParamNotInSearchList) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("height", rtb::ClargParam::ParamType::kInt);
  parser->AddParamToSearchList("size", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-width=500"};
  char third[]{"-height=600"};
  char* argv[3]{first, second, third};

  parser->Parse(3, argv);

  rtb::ClargParam* flag_ptr = parser->GetParam("xpto");
  ASSERT_TRUE(flag_ptr == nullptr);
}

TEST(TestClargParser, IntParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-width=500"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("width");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  int value = std::get<int>(param_ptr->value());
  ASSERT_EQ(value, 500);
}

TEST(TestClargParser, IntParamInvalid) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("angle", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-angle=SO0"};
  char* argv[2]{first, second};

  try {
    parser->Parse(2, argv);
  } catch (...) {
  }

  rtb::ClargParam* param_ptr = parser->GetParam("angle");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  try {
    std::get<int>(param_ptr->value());
  } catch (...) {
    rtb::ClargParam::ErrorCode error =
        std::get<rtb::ClargParam::ErrorCode>(param_ptr->value());
    ASSERT_EQ(error, rtb::ClargParam::ErrorCode::kInvalidArgument);
  }
}

TEST(TestClargParser, IntParamOutOfRange) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("angle", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-angle=100000000000000000000"};
  char* argv[2]{first, second};

  try {
    parser->Parse(2, argv);
  } catch (...) {
  }

  rtb::ClargParam* param_ptr = parser->GetParam("angle");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  try {
    std::get<int>(param_ptr->value());
  } catch (...) {
    rtb::ClargParam::ErrorCode error =
        std::get<rtb::ClargParam::ErrorCode>(param_ptr->value());
    ASSERT_EQ(error, rtb::ClargParam::ErrorCode::kOutOfRange);
  }
}

TEST(TestClargParser, HexIntParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-width=0x500"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("width");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  int value = std::get<int>(param_ptr->value());
  ASSERT_EQ(value, 1280);
}

TEST(TestClargParser, OctIntParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("width", rtb::ClargParam::ParamType::kInt);

  char first[]{"app name"};
  char second[]{"-width=0500"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("width");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  int value = std::get<int>(param_ptr->value());
  ASSERT_EQ(value, 320);
}

TEST(TestClargParser, LongParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("long", rtb::ClargParam::ParamType::kLong);

  char first[]{"app name"};
  char second[]{"-long=-50000"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("long");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  long value = std::get<long>(param_ptr->value());
  ASSERT_EQ(value, -50000);
}

TEST(TestClargParser, LongLongParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("longlong",
                               rtb::ClargParam::ParamType::kLongLong);

  char first[]{"app name"};
  char second[]{"-longlong=-50000"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("longlong");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  long long value = std::get<long long>(param_ptr->value());
  ASSERT_EQ(value, -50000);
}

TEST(TestClargParser, UnsignedLongParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("unsignedlong",
                               rtb::ClargParam::ParamType::kUnsignedLong);

  char first[]{"app name"};
  char second[]{"-unsignedlong=50000"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("unsignedlong");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  unsigned long value = std::get<unsigned long>(param_ptr->value());
  ASSERT_EQ(value, 50000);
}

TEST(TestClargParser, UnsignedLongLongParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("unsignedlonglong",
                               rtb::ClargParam::ParamType::kUnsignedLongLong);

  char first[]{"app name"};
  char second[]{"-unsignedlonglong=50000"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("unsignedlonglong");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  unsigned long long value = std::get<unsigned long long>(param_ptr->value());
  ASSERT_EQ(value, 50000);
}

TEST(TestClargParser, FloatParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("float", rtb::ClargParam::ParamType::kFloat);

  char first[]{"app name"};
  char second[]{"-float=-3.1415"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("float");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  float value = std::get<float>(param_ptr->value());
  ASSERT_FLOAT_EQ(value, -3.1415);
}

TEST(TestClargParser, DoubleParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("double", rtb::ClargParam::ParamType::kDouble);

  char first[]{"app name"};
  char second[]{"-double=-3.1415926"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("double");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  double value = std::get<double>(param_ptr->value());
  ASSERT_DOUBLE_EQ(value, -3.1415926);
}

TEST(TestClargParser, LongDoubleParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("longdouble",
                               rtb::ClargParam::ParamType::kLongDouble);

  char first[]{"app name"};
  char second[]{"-longdouble=-3.141592633333"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("longdouble");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  long double value = std::get<long double>(param_ptr->value());
  ASSERT_DOUBLE_EQ(value, -3.141592633333);
}

TEST(TestClargParser, StringParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("string",
                               rtb::ClargParam::ParamType::kStdString);

  char first[]{"app name"};
  char second[]{"-string=Roger"};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("string");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  std::string value = std::get<std::string>(param_ptr->value());
  ASSERT_STREQ(value.c_str(), "Roger");
}

TEST(TestClargParser, StringWithQuotesParam) {
  rtb::ClargParser* parser = rtb::ClargParser::GetInstance();
  parser->AddParamToSearchList("stringwithquotes",
                               rtb::ClargParam::ParamType::kStdString);

  char first[]{"app name"};
  char second[]{"-stringwithquotes=\"Roger Davies\""};
  char* argv[2]{first, second};

  parser->Parse(2, argv);

  rtb::ClargParam* param_ptr = parser->GetParam("stringwithquotes");
  ASSERT_TRUE(param_ptr != nullptr);
  ASSERT_TRUE(param_ptr->found());
  std::string value = std::get<std::string>(param_ptr->value());
  // ASSERT_STREQ(value.c_str(), "\"Roger Davies\"");
  rtb::Logger::LogInfo(value.c_str());
} */

TEST(TestMatrix, Constructor) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(0.0, m(i, j));
    }
  }
}

TEST(TestMatrix, WriteReadElements) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      m(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(i * cols + j, m(i, j));
    }
  }
}

TEST(TestMatrix, OutOfBoundsRow) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  ASSERT_THROW(m(rows, 0) = 100, std::out_of_range);
}

TEST(TestMatrix, OutOfBoundsCol) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  ASSERT_THROW(m(0, cols) = 100, std::out_of_range);
}

TEST(TestMatrix, CopyConstruction) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      m(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  rtb::Matrix m2(m);

  // m2 should have the same element values as m.
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(i * cols + j, m2(i, j));
    }
  }

  // And if we change m the elements in m2 are not affected.
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      m(i, j) = 0.0;
    }
  }
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(i * cols + j, m2(i, j));
    }
  }
}

TEST(TestMatrix, Assignment) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      m(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  const size_t rows2 = 11;
  const size_t cols2 = 3;
  rtb::Matrix m2(rows2, cols2);

  for (size_t i = 0; i < rows2; i++) {
    for (size_t j = 0; j < cols2; j++) {
      m2(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  m2 = m;

  ASSERT_EQ(m2.Rows(), m.Rows());
  ASSERT_EQ(m2.Cols(), m.Cols());
}

TEST(TestMatrix, IsRowVector) {
  const size_t rows = 1;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  ASSERT_TRUE(m.IsRowVector());
}

TEST(TestMatrix, IsNotRowVector) {
  const size_t rows = 2;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  ASSERT_FALSE(m.IsRowVector());
}

TEST(TestMatrix, IsColVector) {
  const size_t rows = 9;
  const size_t cols = 1;
  rtb::Matrix m(rows, cols);

  ASSERT_TRUE(m.IsColVector());
}

TEST(TestMatrix, IsNotColVector) {
  const size_t rows = 2;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  ASSERT_FALSE(m.IsColVector());
}

TEST(TestMatrix, IsSquare) {
  const size_t rows = 9;
  const size_t cols = 9;
  rtb::Matrix m(rows, cols);

  ASSERT_TRUE(m.IsSquare());
}

TEST(TestMatrix, IsNotSquare) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  ASSERT_FALSE(m.IsSquare());
}

TEST(TestMatrix, IsNotSquare2) {
  const size_t rows = 0;
  const size_t cols = 0;
  rtb::Matrix m(rows, cols);

  ASSERT_FALSE(m.IsSquare());
}

TEST(TestMatrix, Addition) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  rtb::Matrix c(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      b(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
      c(i, j) = 2 * static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  rtb::Matrix a = b + c;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(a(i, j), b(i, j) + c(i, j));
    }
  }
}

TEST(TestMatrix, Addition2) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  rtb::Matrix c(rows, cols);
  rtb::Matrix d(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      b(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
      c(i, j) = 2 * static_cast<double>(i) * cols + static_cast<double>(j);
      d(i, j) = 3 * static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  rtb::Matrix a = b + c + d;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(a(i, j), b(i, j) + c(i, j) + d(i, j));
    }
  }
}

TEST(TestMatrix, AdditionSizeMismatch) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  rtb::Matrix c(rows + 1, cols);

  ASSERT_THROW(rtb::Matrix a = b + c, std::invalid_argument);
}

TEST(TestMatrix, Subtraction) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  rtb::Matrix c(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      b(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
      c(i, j) = 2 * static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  rtb::Matrix a = b - c;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(a(i, j), b(i, j) - c(i, j));
    }
  }
}

TEST(TestMatrix, Subtraction2) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  rtb::Matrix c(rows, cols);
  rtb::Matrix d(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      b(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
      c(i, j) = 2 * static_cast<double>(i) * cols + static_cast<double>(j);
      d(i, j) = 3 * static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  rtb::Matrix a = b - c - d;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(a(i, j), b(i, j) - c(i, j) - d(i, j));
    }
  }
}

TEST(TestMatrix, SubtractionSizeMismatch) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  rtb::Matrix c(rows + 1, cols);

  ASSERT_THROW(rtb::Matrix a = b - c, std::invalid_argument);
}

TEST(TestMatrix, ScalarMultiplication) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix b(rows, cols);
  const double scalar = 3.0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      b(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  rtb::Matrix a = b * scalar;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      ASSERT_DOUBLE_EQ(a(i, j), b(i, j) * scalar);
    }
  }
}

TEST(TestMatrix, Transpose) {
  rtb::Matrix m(2, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 0;
  m(1, 1) = -6;
  m(1, 2) = 7;

  rtb::Matrix t = m.Transpose();
  ASSERT_EQ(m.Rows(), t.Cols());
  ASSERT_EQ(m.Cols(), t.Rows());

  ASSERT_EQ(m(0, 0), t(0, 0));
  ASSERT_EQ(m(0, 1), t(1, 0));
  ASSERT_EQ(m(0, 2), t(2, 0));
  ASSERT_EQ(m(1, 0), t(0, 1));
  ASSERT_EQ(m(1, 1), t(1, 1));
  ASSERT_EQ(m(1, 2), t(2, 1));
}

TEST(TestMatrix, DotProduct) {
  rtb::Matrix a(1, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 3.0;
  a(0, 2) = -5.0;
  rtb::Matrix b(3, 1);
  b(0, 0) = 4.0;
  b(1, 0) = -2.0;
  b(2, 0) = -1.0;

  ASSERT_DOUBLE_EQ(3.0, a.DotProduct(b));
  ASSERT_DOUBLE_EQ(3.0, b.DotProduct(a));
}

TEST(TestMatrix, DotProductNot1D) {
  rtb::Matrix other(9, 1);
  rtb::Matrix m(9, 2);

  double dot_prod = 0.0;
  ASSERT_THROW(dot_prod = m.DotProduct(other), std::invalid_argument);
}

TEST(TestMatrix, DotProductNot1D2) {
  rtb::Matrix other(9, 1);
  rtb::Matrix m(2, 9);

  double dot_prod = 0.0;
  ASSERT_THROW(dot_prod = m.DotProduct(other), std::invalid_argument);
}

TEST(TestMatrix, DotProductOtherNot1D) {
  rtb::Matrix other(9, 2);
  rtb::Matrix m(9, 1);

  double dot_prod = 0.0;
  ASSERT_THROW(dot_prod = m.DotProduct(other), std::invalid_argument);
}

TEST(TestMatrix, DotProductOtherNot1D2) {
  rtb::Matrix other(9, 2);
  rtb::Matrix m(1, 9);

  double dot_prod = 0.0;
  ASSERT_THROW(dot_prod = m.DotProduct(other), std::invalid_argument);
}

TEST(TestMatrix, DotProductSizeMissmatch) {
  rtb::Matrix other(9, 1);
  rtb::Matrix m(1, 7);

  double dot_prod = 0.0;
  ASSERT_THROW(dot_prod = m.DotProduct(other), std::invalid_argument);
}

TEST(TestMatrix, Product) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;
  rtb::Matrix b(3, 2);
  b(0, 0) = 0.0;
  b(0, 1) = 1000.0;
  b(1, 0) = 1.0;
  b(1, 1) = 100.0;
  b(2, 0) = 0.0;
  b(2, 1) = 10.0;

  rtb::Matrix product = a.Multiply(b);

  ASSERT_DOUBLE_EQ(product(0, 0), 3.0);
  ASSERT_DOUBLE_EQ(product(0, 1), 2340.0);
  ASSERT_DOUBLE_EQ(product(1, 0), 0.0);
  ASSERT_DOUBLE_EQ(product(1, 1), 1000.0);
}

TEST(TestMatrix, GetRow) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      m(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  const size_t index = 3;
  rtb::Matrix row = m.GetRow(index);

  ASSERT_EQ(1, row.Rows());
  ASSERT_EQ(cols, row.Cols());

  for (size_t k = 0; k < cols; k++) {
    ASSERT_DOUBLE_EQ(row(0, k), m(index, k));
  }
}

TEST(TestMatrix, GetInvalidRow) {
  const size_t rows = 9;
  const size_t cols = 7;
  rtb::Matrix m(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      m(i, j) = static_cast<double>(i) * cols + static_cast<double>(j);
    }
  }

  const size_t index = 9;
  ASSERT_THROW(rtb::Matrix row = m.GetRow(index), std::invalid_argument);
}

TEST(TestMatrix, AddRowToRow) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;
  rtb::Matrix b(1, 3);
  b(0, 0) = 10.0;
  b(0, 1) = 100.0;
  b(0, 2) = 1000.0;

  a.AddRowToRow(0, b);

  ASSERT_DOUBLE_EQ(a(0, 0), 12.0);
  ASSERT_DOUBLE_EQ(a(0, 1), 103.0);
  ASSERT_DOUBLE_EQ(a(0, 2), 1004.0);
}

TEST(TestMatrix, AddNotRowToRow) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;
  rtb::Matrix b(2, 3);

  ASSERT_THROW(a.AddRowToRow(0, b), std::invalid_argument);
}

TEST(TestMatrix, AddNotSameSizeRowToRow) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;
  rtb::Matrix b(1, 4);

  ASSERT_THROW(a.AddRowToRow(0, b), std::invalid_argument);
}

TEST(TestMatrix, AddRowToInvalidRow) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;
  rtb::Matrix b(1, 3);

  ASSERT_THROW(a.AddRowToRow(2, b), std::invalid_argument);
}

TEST(TestMatrix, SwapRows) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;

  a.SwapRows(0, 1);

  ASSERT_DOUBLE_EQ(a(0, 0), 1.0);
  ASSERT_DOUBLE_EQ(a(0, 1), 0.0);
  ASSERT_DOUBLE_EQ(a(0, 2), 0.0);
  ASSERT_DOUBLE_EQ(a(1, 0), 2.0);
  ASSERT_DOUBLE_EQ(a(1, 1), 3.0);
  ASSERT_DOUBLE_EQ(a(1, 2), 4.0);
}

TEST(TestMatrix, SwapInvalidRows) {
  rtb::Matrix a(2, 3);
  a(0, 0) = 2.0;
  a(0, 1) = 3.0;
  a(0, 2) = 4.0;
  a(1, 0) = 1.0;
  a(1, 1) = 0.0;
  a(1, 2) = 0.0;

  ASSERT_THROW(a.SwapRows(0, 2), std::invalid_argument);
}