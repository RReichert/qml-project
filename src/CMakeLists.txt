# version details
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# qt cmake setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/qt/5.8.0/5.8/gcc_64")

# specify source files
set(SOURCE_FILES main.cpp main_window.cpp main_window.h)
set(UI_FILES)
set(RESOURCE_FILES)

# add current source/binary folder into include directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# load qt5 modules
find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Widgets)

# create executable
add_executable(trial ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES})
qt5_use_modules(trial Core Widgets)