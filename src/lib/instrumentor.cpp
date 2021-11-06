// @file      instrumentor.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "instrumentor.hpp"

namespace rtb {

void Instrumentor::BeginSession(const std::string& name,
                                const std::string& filepath) {
  output_stream_.open(filepath);
  WriteHeader();
  current_session_ptr_ = std::make_unique<rtb_h::InstrumentationSession>(
      rtb_h::InstrumentationSession{name});
}

void Instrumentor::EndSession() {
  WriteFooter();
  output_stream_.close();
  profile_count_ = 0;
}

void Instrumentor::WriteProfile(const rtb_h::ProfileResult& result) {
  if (profile_count_++ > 0) {
    output_stream_ << ",";
  }

  std::string name = result.name;
  std::replace(name.begin(), name.end(), '"', '\'');

  output_stream_ << "{";
  output_stream_ << R"("cat":"function",)";
  output_stream_ << "\"dur\":" << (result.end - result.Start) << ',';
  output_stream_ << R"("name":")" << name << "\",";
  output_stream_ << R"("ph":"X",)";
  output_stream_ << "\"pid\":0,";
  output_stream_ << "\"tid\":" << result.thread_id << ",";
  output_stream_ << "\"ts\":" << result.Start;
  output_stream_ << "}";

  output_stream_.flush();
}

void Instrumentor::WriteHeader() {
  output_stream_ << R"({"otherData": {},"traceEvents":[)";
  output_stream_.flush();
}

void Instrumentor::WriteFooter() {
  output_stream_ << "]}";
  output_stream_.flush();
}

Instrumentor& Instrumentor::GetInstance() {
  static Instrumentor instance_;
  return instance_;
}

InstrumentationTimer::~InstrumentationTimer() {
  if (!stopped_) {
    Stop();
  }
}

void InstrumentationTimer::Stop() {
  auto endTimepoint = std::chrono::high_resolution_clock::now();

  long long start =
      std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint_)
          .time_since_epoch()
          .count();
  long long end =
      std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
          .time_since_epoch()
          .count();

  uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
  Instrumentor::GetInstance().WriteProfile({name_, start, end, threadID});

  stopped_ = true;
}

}  // namespace rtb