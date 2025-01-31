// @file      log_sink.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved
#pragma once

#include <fstream>
#include <iostream>

namespace rtb_h {
enum MessageType { kInfo, kWarning, kError };

/**
 * @brief Abstract class for log sinks.
 *
 */
class LogSink {
 public:
  virtual ~LogSink() = default;

  virtual void Log(const std::string& message, MessageType message_type) = 0;
};

/**
 * @brief Log to stdout.
 *
 */
class LogSinkCout : public LogSink {
 public:
  void Log(const std::string& message, MessageType message_type) override;
};

/**
 * @brief Log to stderr.
 *
 */
class LogSinkCerr : public LogSink {
 public:
  void Log(const std::string& message, MessageType message_type) override;
};

/**
 * @brief Log to 'null' (i.e. do not log).
 *
 */
class LogSinkNull : public LogSink {
 public:
  void Log(const std::string&, MessageType) override {}
};

/**
 * @brief Log to a file.
 *
 */
class LogSinkFile : public LogSink {
 public:
  LogSinkFile() = delete;
  explicit LogSinkFile(std::string filepath);
  ~LogSinkFile() override;
  void Log(const std::string& message, MessageType message_type) override;
  void SetFilePath(const std::string& filepath);

  LogSinkFile(const LogSinkFile&) = delete;
  LogSinkFile& operator=(const LogSinkFile&) = delete;
  LogSinkFile(const LogSinkFile&&) = delete;
  LogSinkFile& operator=(const LogSinkFile&&) = delete;

 private:
  std::ofstream fs_;
  std::string filepath_;

  void OpenLogFile();
};
}  // namespace rtb_h