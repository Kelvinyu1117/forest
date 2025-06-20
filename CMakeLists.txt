cmake_minimum_required(VERSION 3.28)
project(forest)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(forest INTERFACE)
target_include_directories(forest INTERFACE include)


include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_SHALLOW    TRUE
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1)
FetchContent_MakeAvailable(Catch2)


add_subdirectory(tests)

