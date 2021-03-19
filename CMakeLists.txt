cmake_minimum_required(VERSION 3.11)

project(fmath VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

option(FMATH_ENABLE_TEST "Enable the tests" ON)

add_library(fmath INTERFACE)
add_library(fmath::fmath ALIAS fmath)

target_include_directories(fmath INTERFACE include/fmath)

if(FMATH_ENABLE_TEST)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()