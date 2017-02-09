# version details
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# setup qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/qt/5.8.0/5.8/gcc_64")

# source files
set(SOURCE_FILES main.cpp main_window.cpp)
set(UI_FILES main_window.ui)
set(RESOURCE_FILES)

# find configuration packages
find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Widgets)

# project executable
add_executable(trial ${SOURCE_FILES} ${UI_FILES} ${RESOURCE_FILES})
qt5_use_modules(trial Core Widgets)

# project installation
install(
    TARGETS trial
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)