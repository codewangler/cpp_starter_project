// @file      instrumentor.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <string>
#include <thread>

// Useful macros for using the Instrumentor profiler.
#if PROFILING
#define PROFILE_SCOPE(name) rtb::InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#endif

namespace rtb_h {

struct ProfileResult {
  std::string name;
  long long Start, end;
  uint32_t thread_id;
} __attribute__((aligned(64))) __attribute__((packed));

struct InstrumentationSession {
  std::string name;
} __attribute__((aligned(32)));

}  // namespace rtb_h

namespace rtb {

class Instrumentor {
 public:
  void BeginSession(const std::string& name,
                    const std::string& filepath = "instrumentor.json");
  void EndSession();
  void WriteProfile(const rtb_h::ProfileResult& result);
  void WriteHeader();
  void WriteFooter();
  static Instrumentor& GetInstance();

 private:
  std::unique_ptr<rtb_h::InstrumentationSession> current_session_ptr_;
  std::ofstream output_stream_;
  int profile_count_{};

  Instrumentor() = default;
};

class InstrumentationTimer {
 public:
  explicit InstrumentationTimer(const char* name)
      : name_(name),
        start_timepoint_(std::chrono::high_resolution_clock::now()),
        stopped_(false) {}
  ~InstrumentationTimer();
  InstrumentationTimer(const InstrumentationTimer& rhs) = delete;
  InstrumentationTimer operator=(const InstrumentationTimer& rhs) = delete;
  InstrumentationTimer(const InstrumentationTimer&& rhs) = delete;
  InstrumentationTimer operator=(const InstrumentationTimer&& rhs) = delete;
  void Stop();

 private:
  const char* name_;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint_;
  bool stopped_;
};

}  // namespace rtb