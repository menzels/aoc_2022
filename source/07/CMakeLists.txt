cmake_minimum_required(VERSION 3.25)
project(puzzle_07 LANGUAGES CXX)

add_library(puzzle_07)

target_sources(
  puzzle_07
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_07.cpp
)

target_link_libraries(
  puzzle_07
  PRIVATE common
)
