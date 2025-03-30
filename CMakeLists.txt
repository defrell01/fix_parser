cmake_minimum_required(VERSION 3.10)
project(FixParser)

set(CMAKE_CXX_STANDARD 20) 

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(./)
include_directories(./)

add_subdirectory(fixParser)
add_subdirectory(testImpl)