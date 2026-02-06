cmake_minimum_required(VERSION 3.15)
project(DatabaseTesting)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(DatabaseTesting ${SOURCES} "include/DataBaseManager.h")