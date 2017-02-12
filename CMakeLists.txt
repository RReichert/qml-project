# mimimum cmake requirements
cmake_minimum_required(VERSION 3.6)

# c++ language configuration
set(CMAKE_CXX_STANDARD 14)

# installation output paths
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
set(TRANSLATION_OUTPUT_PATH i18n)

# sub-projects
add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)
