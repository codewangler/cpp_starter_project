# ~~~
# @file      CMakeLists.txt
# @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
#
# Copyright (c) 2020 Ignacio Vizzo, all rights reserved
cmake_minimum_required(VERSION 3.1)
project(toolbox)

# Set build type if not set.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# If Debug build define RD_DEBUG, otherwise define NDEBUG 
if(CMAKE_BUILD_TYPE STREQUAL Debug)
add_compile_definitions(RD_DEBUG)
else()
add_compile_definitions(NDEBUG)
endif()

# Build options
# option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
# option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
# option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

# Enable testing
enable_testing()
find_package(GTest REQUIRED)

# Set additional flags.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fstandalone-debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Code Coverage, clang-format, clan=tidy, cppcheck, Configuration:
# include(TestCoverage)
# include(ClangFormat)
# include(StaticAnalyzers)

# Tell CMake where to look for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Use this directory to test your installation script
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/results)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)

# Tell CMake where to look for implementation files
add_subdirectory(src)
add_subdirectory(tests)