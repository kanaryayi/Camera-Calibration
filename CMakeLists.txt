cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(CharucoBoardCreator VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV package in the system
find_package(OpenCV 4.9.0 EXACT REQUIRED)

# Include directories for OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the executable for the Charuco board creation script
add_executable(CharucoBoardGenerator generate_charuco_board.cpp)
add_executable(CharucoBoardDetector detect_charuco_board.cpp)

# Link OpenCV libraries with the executable
target_link_libraries(CharucoBoardGenerator ${OpenCV_LIBS})
target_link_libraries(CharucoBoardDetector ${OpenCV_LIBS})
