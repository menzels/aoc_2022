cmake_minimum_required(VERSION 3.25)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API
    3c375311-a3c9-4396-a187-3227ef642046
)
add_compile_options(/experimental:module)
add_compile_options(
  /stdIfcDir
  "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.35.32019\\ifc\\x64"
)

add_subdirectory(source)
add_subdirectory(source/common)
add_subdirectory(source/01)
add_subdirectory(source/02)
add_subdirectory(source/03)
add_subdirectory(source/04)
add_subdirectory(source/05)
add_subdirectory(source/06)
add_subdirectory(source/07)
add_subdirectory(source/08)
