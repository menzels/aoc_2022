cmake_minimum_required(VERSION 3.25)
project(puzzle_01 LANGUAGES CXX)

include(GenerateExportHeader)

add_library(puzzle_01)

generate_export_header(puzzle_01)

target_sources(
  puzzle_01
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}"
  FILES "${CMAKE_CURRENT_BINARY_DIR}/puzzle_01_export.h"
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_01.cpp
)
