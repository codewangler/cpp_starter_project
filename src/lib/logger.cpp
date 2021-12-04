// @file      logger.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "logger.hpp"

#include <chrono>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <thread>
#include <utility>

namespace rtb {
/**
 * @brief Construct a new Logger object.
 * 
 * @param file_sink_path The path to the log file.
 */
Logger::Logger(std::string file_sink_path)
    : p_cout_sink_(std::make_shared<rtb_h::LogSinkCout>()),
      p_cerr_sink_(std::make_shared<rtb_h::LogSinkCerr>()),
      p_null_sink_(std::make_shared<rtb_h::LogSinkNull>()),
      p_file_sink_(nullptr),
      file_sink_path_(std::move(file_sink_path)) {
  // Set the default mapping of log types to log sinks.
  p_error_ = p_cerr_sink_;
  p_warning_ = p_cerr_sink_;
  p_info_ = p_cout_sink_;
}

/**
 * @brief Get the unique Logger instance.
 * 
 * @return Logger& 
 */
Logger& Logger::GetInstance() {
  static Logger instance("rtb.log");
  return instance;
}

/**
 * @brief Set the error sink type.
 * 
 * @param type 
 */
void Logger::SetErrorSink(SinkType type) {
  GetInstance().SetErrorSinkImpl(type);
}

/**
 * @brief Set the warning sink type.
 * 
 * @param type 
 */
void Logger::SetWarningSink(SinkType type) {
  GetInstance().SetWarningSinkImpl(type);
}

/**
 * @brief Set the info sink type.
 * 
 * @param type 
 */
void Logger::SetInfoSink(SinkType type) { GetInstance().SetInfoSinkImpl(type); }

/**
 * @brief Set the error sink implementation.
 * 
 * @param type 
 */
void Logger::SetErrorSinkImpl(SinkType type) { SetSink(type, &p_error_); }

/**
 * @brief Set the warning sink implementation.
 * 
 * @param type 
 */
void Logger::SetWarningSinkImpl(SinkType type) { SetSink(type, &p_warning_); }

/**
 * @brief Set the info sink implementation.
 * 
 * @param type 
 */
void Logger::SetInfoSinkImpl(SinkType type) { SetSink(type, &p_info_); }

/**
 * @brief Set the path to the log file.
 * 
 * @param filepath 
 */
void Logger::SetFileSinkPath(const std::string& filepath) {
  GetInstance().SetFileSinkPathImpl(filepath);
}

/**
 * @brief Set the file sink log file path implementation.
 * 
 * @param filepath 
 */
void Logger::SetFileSinkPathImpl(const std::string& filepath) {
  file_sink_path_ = filepath;
  if (p_file_sink_ != nullptr) {
    auto p = std::dynamic_pointer_cast<rtb_h::LogSinkFile>(p_file_sink_);
    if (p != nullptr) {
      p->SetFilePath(filepath);
    }
  }
}

/**
 * @brief Assign a sink to the sink type.
 * 
 * @param type      The sink type.
 * @param sink_ptr  A pointer to the sink.
 */
void Logger::SetSink(SinkType type, std::shared_ptr<rtb_h::LogSink>* sink_ptr) {
  switch (type) {
    case kSinkCerr:
      *sink_ptr = p_cerr_sink_;
      break;
    case kSinkCout:
      *sink_ptr = p_cout_sink_;
      break;
    case kSinkNull:
      *sink_ptr = p_null_sink_;
      break;
    case kSinkFile:
      if (p_file_sink_ == nullptr) {
        p_file_sink_ = std::make_shared<rtb_h::LogSinkFile>(file_sink_path_);
      }
      *sink_ptr = p_file_sink_;
    default:
      break;
  }
}

/**
 * @brief Get a timestamp for the message.
 * 
 * @return std::string The timestamp as a formattted string.
 */
std::string Logger::GetTimestamp() {
  auto in_time_t =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::ostringstream ss;

  // Because std::localtime is not thread-safe protect access with a mutex.
  std::mutex localtime_mutex;
  const std::lock_guard<std::mutex> lock(localtime_mutex);

  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X ");
  return ss.str();
}
}  // namespace rtb