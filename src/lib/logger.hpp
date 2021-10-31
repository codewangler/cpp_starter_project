// @file      logger.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved
#pragma once

#include <memory>
#include <sstream>

#include "log_sink.hpp"

namespace rtb {
/**
 * @brief Singleton class for logging errors, warnings and information. The
 * class can handle any type that implements operator<<.
 *
 */
class Logger {
 public:
  enum SinkType { kSinkCerr = 0, kSinkCout, kSinkNull, kSinkFile };

  explicit Logger(std::string file_sink_path);
  
  Logger() = delete;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
  Logger(const Logger &&) = delete;
  Logger &operator=(const Logger &&) = delete;
  ~Logger() = default;

  template <typename T>
  static void LogError(const T &value) {
    GetInstance().LogErrorImpl(value);
  }

  template <typename T>
  static void LogError(const T &value, const std::string &message) {
    GetInstance().LogErrorImpl(value, message);
  }

  template <typename T>
  static void LogWarning(const T &value) {
    GetInstance().LogWarningImpl(value);
  }

  template <typename T>
  static void LogWarning(const T &value, const std::string &message) {
    GetInstance().LogWarningImpl(value, message);
  }

  template <typename T>
  static void LogInfo(const T &value) {
    GetInstance().LogInfoImpl(value);
  }

  template <typename T>
  static void LogInfo(const T &value, const std::string &message) {
    GetInstance().LogInfoImpl(value, message);
  }

  static void SetErrorSink(SinkType type);

  static void SetWarningSink(SinkType type);

  static void SetInfoSink(SinkType type);

  static void SetFileSinkPath(const std::string &filepath);

  static std::string GetTimestamp();

 private:
  // Log line prefixes.
  const std::string kErrorPrefix = "[Err] ";
  const std::string kWarningPrefix = "[Wrn] ";
  const std::string kInfoPrefix = "[Inf] ";

  // Pointers to the different possible sinks.
  std::shared_ptr<rtb_h::LogSink> p_cout_sink_;
  std::shared_ptr<rtb_h::LogSink> p_cerr_sink_;
  std::shared_ptr<rtb_h::LogSink> p_null_sink_;
  std::shared_ptr<rtb_h::LogSink> p_file_sink_;

  // Pointers to the sinks associated with each log type.
  std::shared_ptr<rtb_h::LogSink> p_error_;
  std::shared_ptr<rtb_h::LogSink> p_warning_;
  std::shared_ptr<rtb_h::LogSink> p_info_;

  std::string file_sink_path_;

  /**
   * @brief Get the unique instance of Logger.
   * 
   */
  static Logger &GetInstance();

  template <typename T>
  void LogErrorImpl(const T &value) const {
    std::ostringstream buffer;
    buffer << kErrorPrefix << GetTimestamp() << value;
    p_error_->Log(buffer.str());
  }

  template <typename T>
  void LogErrorImpl(const T &value, const std::string &message) const {
    std::ostringstream buffer;
    buffer << kErrorPrefix << GetTimestamp() << message << ": " << value;
    p_error_->Log(buffer.str());
  }

  template <typename T>
  void LogWarningImpl(const T &value) const {
    std::ostringstream buffer;
    buffer << kWarningPrefix << GetTimestamp() << value;
    p_warning_->Log(buffer.str());
  }

  template <typename T>
  void LogWarningImpl(const T &value, const std::string &message) const {
    std::ostringstream buffer;
    buffer << kWarningPrefix << GetTimestamp() << message << ": " << value;
    p_warning_->Log(buffer.str());
  }

  template <typename T>
  void LogInfoImpl(const T &value) const {
    std::ostringstream buffer;
    buffer << kInfoPrefix << GetTimestamp() << value;
    p_info_->Log(buffer.str());
  }

  template <typename T>
  void LogInfoImpl(const T &value, const std::string &message) const {
    std::ostringstream buffer;
    buffer << kInfoPrefix << GetTimestamp() << message << ": " << value;
    p_info_->Log(buffer.str());
  }

  void SetErrorSinkImpl(SinkType type);

  void SetWarningSinkImpl(SinkType type);

  void SetInfoSinkImpl(SinkType type);

  void SetFileSinkPathImpl(const std::string &filepath);

  void SetSink(SinkType type, std::shared_ptr<rtb_h::LogSink> *p_sink);
};
}  // namespace rtb