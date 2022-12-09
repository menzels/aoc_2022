cmake_minimum_required(VERSION 3.25)
project(puzzle_08 LANGUAGES CXX)

add_library(puzzle_08)

target_sources(
  puzzle_08
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_08.cpp
)

target_link_libraries(
  puzzle_08
  PRIVATE common
)
