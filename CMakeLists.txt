# mimimum cmake requirements
cmake_minimum_required(VERSION 3.6)

# project name
project(qml-project)

# project c++ language configuration
set(CMAKE_CXX_STANDARD 14)

# specify target output directories
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# process sub-projects
add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)
