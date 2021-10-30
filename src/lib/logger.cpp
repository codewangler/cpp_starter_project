// @file      logger.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "logger.hpp"

#include <utility>

namespace rtb {
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

Logger& Logger::GetInstance() {
  static Logger instance("rtb.log");
  return instance;
}

void Logger::SetErrorSink(SinkType type) {
  GetInstance().SetErrorSinkImpl(type);
}

void Logger::SetWarningSink(SinkType type) {
  GetInstance().SetWarningSinkImpl(type);
}

void Logger::SetInfoSink(SinkType type) { GetInstance().SetInfoSinkImpl(type); }

void Logger::SetErrorSinkImpl(SinkType type) { SetSink(type, &p_error_); }

void Logger::SetWarningSinkImpl(SinkType type) { SetSink(type, &p_error_); }

void Logger::SetInfoSinkImpl(SinkType type) { SetSink(type, &p_error_); }

void Logger::SetFileSinkPath(const std::string& filepath) {
  GetInstance().SetFileSinkPathImpl(filepath);
}

void Logger::SetFileSinkPathImpl(const std::string& filepath) {
  file_sink_path_ = filepath;
  if (p_file_sink_ != nullptr) {
    auto p = std::dynamic_pointer_cast<rtb_h::LogSinkFile>(p_file_sink_);
    if (p != nullptr) {
      p->SetFilePath(filepath);
    }
  }
}

void Logger::SetSink(SinkType type, std::shared_ptr<rtb_h::LogSink>* p_sink) {
  switch (type) {
    case kSinkCerr:
      *p_sink = p_cerr_sink_;
      break;
    case kSinkCout:
      *p_sink = p_cout_sink_;
      break;
    case kSinkNull:
      *p_sink = p_null_sink_;
      break;
    case kSinkFile:
      if (p_file_sink_ == nullptr) {
        p_file_sink_ = std::make_shared<rtb_h::LogSinkFile>(file_sink_path_);
      }
      *p_sink = p_file_sink_;
    default:
      break;
  }
}
}  // namespace rtb