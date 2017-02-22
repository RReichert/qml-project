# mimimum cmake requirements
cmake_minimum_required(VERSION 3.6)

# compile scripts
add_subdirectory(script)

# project details
project(qml-project)
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# project files
set(MAIN_FILE src/main.cpp)
set(HEADER_FILES
	src/quadratic.h
)
set(SOURCE_FILES
	src/quadratic.cpp
)
set(QML_FILES
	ui/main.qml
)
set(UNIT_TEST_FILES
	test/basic_test.cpp
)
set(TS_FILES
	i18n/lang_pt.ts
	i18n/lang_en.ts
)

# c++ language configuration
set(CMAKE_CXX_STANDARD 14)

# qt framework configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/qt/5.8.0/5.8/gcc_64")

# find external libraries/binaries
find_package(GTest)
find_package(Doxygen)
find_package(Boost REQUIRED)
find_package(Qt5 CONFIG REQUIRED COMPONENTS LinguistTools Qml Quick)

# create necessary source directory folders
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/i18n)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/i18n)
endif()

# generate custom commands for qt translation files (*.ts/*.qm)
qt5_create_translation(QM_FILES ${TS_FILES} ${SOURCE_FILES} ${QML_FILES})

# custom command for i18n/ui resource files
add_custom_command(OUTPUT i18n.qrc
	COMMAND qrc-editor --global_prefix="/i18n" --relative_path="${CMAKE_CURRENT_SOURCE_DIR}" i18n.qrc ${QM_FILES}
	COMMENT "Generating internationalization resource file"
	DEPENDS ${QM_FILES}
)
add_custom_command(OUTPUT ui.qrc
	COMMAND qrc-editor --global_prefix="/ui" --relative_path="${CMAKE_CURRENT_SOURCE_DIR}" ui.qrc ${QML_FILES}
	COMMENT "Generating ui resource file"
	DEPENDS ${QML_FILES}
)

# custom target to translations from project files
add_custom_target(lupdate
	COMMENT "Extracting translatable messages from source code"
	DEPENDS ${TS_FILES}
)

# custom target to generate resource files
add_custom_target(qrc
	COMMENT "Generating qrc files"
	DEPENDS i18n.qrc ui.qrc
)

# executable
add_executable(application ${MAIN_FILE} ${SOURCE_FILES} i18n.qrc ui.qrc)
add_dependencies(application qrc)

target_link_libraries(application ${Boost_LIBRARIES})
target_include_directories(application PUBLIC ${Boost_INCLUDE_DIRS})

qt5_use_modules(application Qml Quick)

# installation
install(
	TARGETS application
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)

# enable documentation target if doxygen is available
if(DOXYGEN_FOUND)

	# documentation configuration settings
	set(USE_MATHJAX "YES")

	# documentation configuration file
	configure_file(Doxyfile.in Doxyfile)

	# documentation compile
	add_custom_target(
		documentation
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
	)

	# documentation installation
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION doc)

endif()


# enable unit test target if gtest is available
if(GTest_FOUND)

	# unit tests compile
	add_executable(unit-tests ${SOURCE_FILES} ${UNIT_TEST_FILES})

	target_link_libraries(unit-tests ${GTEST_BOTH_LIBRARIES})
	target_include_directories(unit-tests PUBLIC ${GTEST_INCLUDE_DIRS})

	# unit tests installation
	install(
        TARGETS unit-tests
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
	)

endif()