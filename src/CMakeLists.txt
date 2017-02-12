# project name
project(qml-project)

# project version details
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# qt framework setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/qt/5.8.0/5.8/gcc_64")

# project files
set(SOURCE_FILES main.cpp)
set(RESOURCE_FILES qml.qrc)

set(TRANSLATION_FILES
    ${CMAKE_SOURCE_DIR}/${TRANSLATION_OUTPUT_PATH}/${PROJECT_NAME}_de.ts
    ${CMAKE_SOURCE_DIR}/${TRANSLATION_OUTPUT_PATH}/${PROJECT_NAME}_pt.ts
)

# packages configuration
find_package(Boost REQUIRED)
find_package(Qt5 CONFIG REQUIRED COMPONENTS LinguistTools Qml Quick)

# project executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RESOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

# qt5_add_translation()
qt5_use_modules(${PROJECT_NAME} Qml Quick)

# project translations
qt5_create_translation(QM_FILES ${SOURCE_FILES} ${TRANSLATION_FILES})

# project installation
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)
