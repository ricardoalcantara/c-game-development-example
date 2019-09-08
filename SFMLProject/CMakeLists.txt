cmake_minimum_required (VERSION 3.0)

project (SFMLProject)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(SFMLProject ${PROJECT_SOURCE_DIR}/src/source.cpp)