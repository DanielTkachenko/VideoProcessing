# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(VideoProcessing VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES src/*.cpp)

# Add the executable
add_executable(VideoProcessing ${SOURCES})