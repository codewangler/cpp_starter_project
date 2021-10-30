// @file      log_sink.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved
#pragma once

#include <fstream>
#include <iostream>

namespace rtb_h {
/**
 * @brief Abstract class for log sinks.
 *
 */
class LogSink {
 public:
  virtual void Log(const std::string &line) = 0;
  virtual ~LogSink() = default;
};

/**
 * @brief Log to stdout.
 *
 */
class LogSinkCout : public LogSink {
 public:
  void Log(const std::string &line) override;
};

/**
 * @brief Log to stderr.
 *
 */
class LogSinkCerr : public LogSink {
 public:
  void Log(const std::string &line) override;
};

/**
 * @brief Log to 'null' (i.e. do not log).
 *
 */
class LogSinkNull : public LogSink {
 public:
  void Log(const std::string &) override {}
};

/**
 * @brief Log to a file.
 *
 */
class LogSinkFile : public LogSink {
 public:
  LogSinkFile() = delete;
  explicit LogSinkFile(std::string filepath);
  LogSinkFile(const LogSinkFile& rhs) = delete;
  LogSinkFile operator=(const LogSinkFile &rhs) = delete;
  LogSinkFile(const LogSinkFile &&rhs) = delete;
  LogSinkFile operator=(const LogSinkFile &&rhs) = delete;
  ~LogSinkFile() override;
  void Log(const std::string &line) override;
  void SetFilePath(const std::string &filepath);

 private:
  std::ofstream fs_;
  std::string filepath_;

  void OpenLogFile();
};
}  // namespace rtb_h