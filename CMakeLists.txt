# cmake needs this line
cmake_minimum_required(VERSION 3.9)

# Define project name
project(SudokuGrabber)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
  src/main.cpp
  src/calculateIntersections.cpp
  src/detectLines.cpp
  src/findBiggestBlob.cpp
  src/findExtremeLines.cpp
  src/preprocessingImage.cpp
  src/undistort.cpp
  )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

if(CMAKE_VERSION VERSION_LESS "2.8.11")
    # Add OpenCV headers location to your include paths
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

# Set include directories
include_directories("include/")

# Declare the executable target built from your sources
add_executable(SudokuGrabber ${SOURCE_FILES})

# Link your application with OpenCV libraries
target_link_libraries(SudokuGrabber ${OpenCV_LIBS})
