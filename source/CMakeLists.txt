cmake_minimum_required(VERSION 3.25)
project(main LANGUAGES CXX)

add_executable(main main.cpp)

target_link_libraries(
  main
  PRIVATE puzzle_01 puzzle_02 puzzle_03 puzzle_04
)
