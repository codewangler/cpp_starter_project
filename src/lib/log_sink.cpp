// @file      log_sink.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "log_sink.hpp"

#include <utility>

namespace rtb_h {
void LogSinkCout::Log(const std::string &line) {
  std::cout << line << std::endl;
}

void LogSinkCerr::Log(const std::string &line) {
  std::cerr << line << std::endl;
}

LogSinkFile::LogSinkFile(std::string filepath) : filepath_(std::move(filepath)) {
  OpenLogFile();
}

LogSinkFile::~LogSinkFile() {
  if (fs_.is_open()) {
    fs_.close();
  }
}

void LogSinkFile::Log(const std::string &line) { fs_ << line << std::endl; }

void LogSinkFile::SetFilePath(const std::string &filepath) {
  if (filepath != filepath_) {
    filepath_ = filepath;
    OpenLogFile();
  }
}

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