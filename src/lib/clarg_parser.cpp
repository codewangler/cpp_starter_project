// @file      clarg_parser.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "clarg_parser.hpp"

#include <algorithm>
#include <string>

#include "toolbox.hpp"

namespace rtb {
/**
 * @brief Get the unique ClargParser instance.
 *
 * @return ClargParser*
 */
ClargParser* ClargParser::GetInstance() {
  static ClargParser instance;
  return &instance;
}

/**
 * @brief Add a command line flag to the flag search list.
 *
 * @param name The name of the flag.
 */
void ClargParser::AddFlagToSearchList(const std::string& name) {
  for (const auto& flag : flags_) {
    if (flag.name() == name) {
      return;
    }
  }

  flags_.emplace_back(name);
}

/**
 * @brief Get a command line flag.
 *
 * @param name The name of the flag.
 * @return ClargFlag*
 */
ClargFlag* ClargParser::GetFlag(const std::string& name) {
  for (auto& flag : flags_) {
    if (flag.name() == name) {
      return &flag;
    }
  }

  return nullptr;
}

/**
 * @brief Add a command line parameter to the parameter search list.
 *
 * @param name        The name of the parameter.
 * @param param_type  The type of the parameter.
 */
void ClargParser::AddParamToSearchList(const std::string& name,
                                       const ClargParam::ParamType param_type) {
  for (const auto& param : params_) {
    if (param.name() == name) {
      return;
    }
  }

  params_.emplace_back(name, param_type);
}

/**
 * @brief Get a command line parameter.
 *
 * @param name The name of the parameter.
 * @return ClargParam*
 */
ClargParam* ClargParser::GetParam(const std::string& name) {
  for (auto& param : params_) {
    if (param.name() == name) {
      return &param;
    }
  }

  return nullptr;
}

/**
 * @brief Search the command line for the flags and parameters in the respective
 * search lists.
 *
 * @param argc  The command line argument count.
 * @param argv  The C-style string array of command line arguments.
 */
void ClargParser::Parse(int const argc, char* argv[]) {
  if (argc > 1) {
    ParseFlags(argc, argv);
    ParseParams(argc, argv);
  }
}

/**
 * @brief Search the command line for flags from the flag search list and set
 * their value.
 *
 * @param argc  The command line argument count.
 * @param argv  The C-style string array of command line arguments.
 */
void ClargParser::ParseFlags(int const argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);
    for (auto& flag : flags_) {
      if (flag.key() == arg) {
        flag.found() = true;
        flag.value() = true;
      }
    }
  }
}

/**
 * @brief Search the command line for parameters from the parameter search list
 * and if found set their value.
 *
 * @param argc  The command line argument count.
 * @param argv  The C-style string array of command line arguments.
 */
void ClargParser::ParseParams(int const argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);
    for (auto& param : params_) {
      std::string::size_type pos = 0;
      pos = arg.find(param.key());
      if (pos == 0) {
        param.found() = true;
        param.raw_value(arg.substr(param.key().size(), arg.size()));
        try {
          switch (param.param_type()) {
            case ClargParam::ParamType::kInt:
              param.value() = std::stoi(param.raw_value(), nullptr, 0);
              break;
            case ClargParam::ParamType::kLong:
              param.value() = std::stol(param.raw_value());
              break;
            case ClargParam::ParamType::kLongLong:
              param.value() = std::stoll(param.raw_value());
              break;
            case ClargParam::ParamType::kUnsignedLong:
              param.value() = std::stoul(param.raw_value());
              break;
            case ClargParam::ParamType::kUnsignedLongLong:
              param.value() = std::stoull(param.raw_value());
              break;
            case ClargParam::ParamType::kFloat:
              param.value() = std::stof(param.raw_value());
              break;
            case ClargParam::ParamType::kDouble:
              param.value() = std::stod(param.raw_value());
              break;
            case ClargParam::ParamType::kLongDouble:
              param.value() = std::stold(param.raw_value());
              break;
            case ClargParam::ParamType::kStdString:
              param.value() = param.raw_value();
              break;
            default:
              rtb::Logger::LogError(
                  "ClargParser::ParseParams: Unknown command line parameter "
                  "type.");
              break;
          }
        } catch (const std::invalid_argument& e) {
          param.value() = ClargParam::ErrorCode::kInvalidArgument;
        } catch (const std::out_of_range& e) {
          param.value() = ClargParam::ErrorCode::kOutOfRange;
        }
      }
    }
  }
}
}  // namespace rtb