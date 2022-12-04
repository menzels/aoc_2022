cmake_minimum_required(VERSION 3.25)
project(puzzle_03 LANGUAGES CXX)

add_library(puzzle_03)

target_sources(
  puzzle_03
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_03.cpp
)
