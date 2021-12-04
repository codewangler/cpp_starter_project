// @file      log_sink.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "log_sink.hpp"

#include <utility>

namespace rtb_h {
// Message text colour escape sequences.
const std::string kTextColorRed{"\033[0;31m"};
const std::string kTextColorYellow{"\033[0;33m"};
const std::string kTextColorReset{"\033[0m"};

/**
 * @brief Log a message to stdout.
 *
 * @param message       The message.
 * @param message_type  The message type.
 */
void LogSinkCout::Log(const std::string& message,
                      const MessageType message_type) {
  switch (message_type) {
    case kError:
      std::cout << kTextColorRed + message + kTextColorReset << std::endl;
      break;
    case kWarning:
      std::cout << kTextColorYellow + message + kTextColorReset << std::endl;
      break;
    case kInfo:
      std::cout << message << std::endl;
      break;
  }
}

/**
 * @brief Log a message to stderr.
 *
 * @param message       The message.
 * @param message_type  The message type.
 */
void LogSinkCerr::Log(const std::string& message,
                      const MessageType message_type) {
  switch (message_type) {
    case kError:
      std::cerr << kTextColorRed + message + kTextColorReset << std::endl;
      break;
    case kWarning:
      std::cerr << kTextColorYellow + message + kTextColorReset << std::endl;
      break;
    case kInfo:
      std::cerr << message << std::endl;
      break;
  }
}

/**
 * @brief Construct a new LogSinkFile object and open the log file.
 *
 * @param filepath
 */
LogSinkFile::LogSinkFile(std::string filepath)
    : filepath_(std::move(filepath)) {
  OpenLogFile();
}

/**
 * @brief Destroy the LogSinkFile object and clode the log file.
 * 
 */
LogSinkFile::~LogSinkFile() {
  if (fs_.is_open()) {
    fs_.close();
  }
}

/**
 * @brief Log a message to the log file.
 *
 * @param message       The message.
 * @param message_type  The message type.
 */
void LogSinkFile::Log(const std::string& message, const MessageType) {
  fs_ << message << std::endl;
}

/**
 * @brief Set the path to the log file.
 * 
 * @param filepath 
 */
void LogSinkFile::SetFilePath(const std::string& filepath) {
  if (filepath != filepath_) {
    filepath_ = filepath;
    OpenLogFile();
  }
}

/**
 * @brief Open the log file.
 * 
 */
void LogSinkFile::OpenLogFile() {
  if (fs_.is_open()) {
    fs_.close();
  }
  fs_ = std::ofstream(filepath_, std::ios::out);
  if (!fs_.good()) {
    std::cerr << "Error opening log file " << filepath_ << std::endl;
  }
}
}  // namespace rtb_h