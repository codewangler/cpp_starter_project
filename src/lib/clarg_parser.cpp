// @file      clarg_parser.cpp
// @author    Roger Davies     [rdavies3000@gmail.com]
//
// Copyright (c) 2021 Roger Davies, all rights reserved

#include "clarg_parser.hpp"

#include <algorithm>

namespace rtb {
ClargParser* ClargParser::GetInstance() {
  static ClargParser instance;
  return &instance;
}

void ClargParser::AddFlagToSearchList(const std::string& name) {
  for (const auto& flag : flags_) {
    if (flag.name() == name) {
      return;
    }
  }

  flags_.emplace_back(name);
}

ClargFlag* ClargParser::GetFlag(const std::string& name) {
  for (auto& flag : flags_) {
    if (flag.name() == name) {
      return &flag;
    }
  }
  return nullptr;
}

void ClargParser::AddParamToSearchList(const std::string& name) {
  for (const auto& param : params_) {
    if (param.name() == name) {
      return;
    }
  }
  params_.emplace_back(name);
}

ClargParam* ClargParser::GetParam(const std::string& name) {
  for (auto& param : params_) {
    if (param.name() == name) {
      return &param;
    }
  }
  return nullptr;
}

void ClargParser::Parse(int const argc, char* argv[]) {
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::string arg(argv[i]);
      for (auto& flag : flags_) {
        if (flag.key() == arg) {
          flag.found() = true;
          flag.value() = true;
        }
      }

      for (auto& param : params_) {
        std::string::size_type pos = 0;
        pos = arg.find(param.key());
        if (pos == 0) {
          param.found() = true;
          param.value(arg.substr(param.key().size(), arg.size()));
        }
      }
    }
  }
}

}  // namespace rtb