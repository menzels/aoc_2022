cmake_minimum_required(VERSION 3.25)
project(puzzle_06 LANGUAGES CXX)

add_library(puzzle_06)

target_sources(
  puzzle_06
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_06.cpp
)

target_link_libraries(
  puzzle_06
  PRIVATE common
)
