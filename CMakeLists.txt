cmake_minimum_required(VERSION 3.10)
project(json_parsing_library)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(json_parser ${SOURCES})

# Include directories
include_directories(include)
