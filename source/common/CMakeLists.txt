cmake_minimum_required(VERSION 3.25)
project(common LANGUAGES CXX)

add_library(common)

target_sources(
  common
  PUBLIC
  FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES string_generator.cpp
)
