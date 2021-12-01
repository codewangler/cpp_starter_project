// @file      clarg_parser.hpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace rtb {
/**
 * @brief Base command line argument class.
 *
 */
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

/**
 * @brief Command line argument flag. If the flag is found it's value is "true",
 * otherwise it's value is "false".
 *
 */
class ClargFlag : public ClargArg {
 public:
  explicit ClargFlag(const std::string& name) : ClargArg(name) {
    key() = kPrefix + name;
  }
  [[nodiscard]] bool value() const { return value_; }
  bool& value() { return value_; }

 private:
  bool value_{false};

  const std::string kPrefix = "-";
};

/**
 * @brief Command line argument parameter. If the parameter is found the
 * ClargParser will attempt to convert the raw string to the specified type.
 *
 */
class ClargParam : public ClargArg {
 public:
  /**
   * @brief The supported parameter types.
   *
   */
  enum class ParamType {
    kInt,
    kLong,
    kLongLong,
    kUnsignedLong,
    kUnsignedLongLong,
    kFloat,
    kDouble,
    kLongDouble,
    kStdString
  };

  /**
   * @brief The string-to-type conversion error codes.
   *
   */
  enum class ErrorCode { kInvalidArgument, kOutOfRange };

  // This variant can contain all supported types plus the ErrorCode enum.
  using var_type = std::variant<int, long, long long, unsigned long,
                                unsigned long long, float, double, long double,
                                std::string, ClargParam::ErrorCode>;

  explicit ClargParam(const std::string& name, ParamType type)
      : ClargArg(name), param_type_(type) {
    key() = kPrefix + name + kPostfix;
  }
  [[nodiscard]] std::string raw_value() const { return raw_value_; }
  void raw_value(const std::string& value) { raw_value_ = value; }
  [[nodiscard]] ParamType param_type() const { return param_type_; }
  [[nodiscard]] var_type value() const { return value_; }
  var_type& value() { return value_; }

 private:
  std::string raw_value_;
  ParamType param_type_;
  var_type value_;

  const std::string kPrefix = "-";
  const std::string kPostfix = "=";
};

/**
 * @brief The command line argument parser class is a Singleton.
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
  
  void AddParamToSearchList(const std::string& name,
                            ClargParam::ParamType param_type);
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
  void ParseFlags(int argc, char* argv[]);
  void ParseParams(int argc, char* argv[]);

  std::vector<ClargFlag> flags_;
  std::vector<ClargParam> params_;
};
}  // namespace rtb