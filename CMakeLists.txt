cmake_minimum_required(VERSION 3.11)

project(fmath VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(fmath INTERFACE)
add_library(fmath::fmath ALIAS fmath)

target_include_directories(fmath INTERFACE include/fmath)