cmake_minimum_required(VERSION 3.25)
project(puzzle_04 LANGUAGES CXX)

add_library(puzzle_04)

target_sources(
  puzzle_04
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_04.cpp
)

target_link_libraries(
  puzzle_04
  PRIVATE common
)
