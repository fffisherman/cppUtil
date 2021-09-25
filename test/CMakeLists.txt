cmake_minimum_required(VERSION 3.0)  # CMake version check
project(util_example)               # Create project "simple_example"
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11")
# Add main.cpp file of project root directory as source file

#include_directories(SYSTEM ${JSON_PATH}/include)
include_directories("../")
FILE(GLOB SC_FILES "../*.cpp" )
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(string_test string_util_test.cpp ${SC_FILES})
