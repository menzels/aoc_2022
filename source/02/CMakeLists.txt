cmake_minimum_required(VERSION 3.25)
project(puzzle_02 LANGUAGES CXX)

add_library(puzzle_02)

target_sources(
  puzzle_02
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES puzzle_02.cpp
)
