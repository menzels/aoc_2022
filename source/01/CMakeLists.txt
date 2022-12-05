cmake_minimum_required(VERSION 3.25)
project(puzzle_01 LANGUAGES CXX)

add_library(puzzle_01)

target_sources(
  puzzle_01
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_01.cpp
)

target_link_libraries(
  puzzle_01
  PRIVATE common
)
