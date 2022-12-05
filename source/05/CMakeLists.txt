cmake_minimum_required(VERSION 3.25)
project(puzzle_05 LANGUAGES CXX)

add_library(puzzle_05)

target_sources(
  puzzle_05
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_05.cpp
)

target_link_libraries(
  puzzle_05
  PRIVATE common
)
