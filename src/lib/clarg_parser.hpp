// @file      clarg_parser.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace rtb {
class ClargArg {
 public:
  explicit ClargArg(std::string name) : name_(std::move(name)) {}
  [[nodiscard]] std::string name() const { return name_; }
  bool& found() { return found_; }
  [[nodiscard]] bool found() const { return found_; }
  std::string& key() { return key_; }
  [[nodiscard]] std::string key() const { return key_; }

 private:
  std::string name_;
  std::string key_;
  bool found_{false};
};

class ClargFlag : public ClargArg {
 public:
  explicit ClargFlag(const std::string& name) : ClargArg(name) {
    key() = kPrefix + name;
  }
  bool& value() { return value_; }
  [[nodiscard]] bool value() const { return value_; }

 private:
  bool value_{false};

  const std::string kPrefix = "-";
};

class ClargParam : public ClargArg {
 public:
  explicit ClargParam(const std::string& name) : ClargArg(name) {
    key() = kPrefix + name + kPostfix;
  }
  [[nodiscard]] std::string value() const { return value_; }
  void value(const std::string& value) { value_ = value; }

 private:
  std::string value_;

  const std::string kPrefix = "-";
  const std::string kPostfix = "=";
};

/**
 * @brief This command line argument parser class is a Singleton.
 *
 */
class ClargParser {
 public:
  static ClargParser* GetInstance();

  void AddFlagToSearchList(const std::string& name);
  [[nodiscard]] unsigned int GetFlagSearchListCount() const {
    return flags_.size();
  }
  [[nodiscard]] ClargFlag* GetFlag(const std::string& name);

  void AddParamToSearchList(const std::string& name);
  [[nodiscard]] unsigned int GetParamSearchListCount() const {
    return params_.size();
  }
  [[nodiscard]] ClargParam* GetParam(const std::string& name);

  void Parse(int argc, char* argv[]);

  ~ClargParser() = default;
  ClargParser(const ClargParser&) = delete;
  ClargParser& operator=(const ClargParser&) = delete;
  ClargParser(const ClargParser&&) = delete;
  ClargParser& operator=(const ClargParser&&) = delete;

 private:
  ClargParser() = default;

  std::vector<ClargFlag> flags_;
  std::vector<ClargParam> params_;
};
}  // namespace rtb