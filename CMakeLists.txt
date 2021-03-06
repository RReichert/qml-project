# mimimum cmake requirements
cmake_minimum_required(VERSION 3.6)

# project details
project(qml-project)
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# c++ language configuration
set(CMAKE_CXX_STANDARD 14)

# qt framework configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_PREFIX_PATH "/opt/qt/5.8.0/5.8/gcc_64")

# process scripts
add_subdirectory(script)

# find external libraries/binaries
find_package(GTest)
find_package(Doxygen)
find_package(Boost REQUIRED)
find_package(Qt5 CONFIG REQUIRED COMPONENTS LinguistTools Qml Quick)

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
set(TEST_FILES
	test/basic_test.cpp
)
set(TS_FILES
	i18n/lang_pt.ts
	i18n/lang_en.ts
)

# custom commands for translation files (*.ts/*.qm)
qt5_create_translation(QM_FILES ${TS_FILES} ${HEADER_FILES} ${SOURCE_FILES} ${QML_FILES})

# custom command for resource files
add_custom_command(OUTPUT i18n.qrc
	COMMAND qt5-create-qrc -p="/i18n" ${QM_FILES}
	DEPENDS ${QM_FILES}
)

add_custom_command(OUTPUT ui.qrc
	COMMAND qt5-create-qrc -p="/ui" ${QML_FILES}
	DEPENDS ${QM_FILES}
)

# executable
add_executable(application ${MAIN_FILE} ${SOURCE_FILES}) # i18n.qrc ui.qrc

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
	add_executable(unit-tests ${SOURCE_FILES} ${TEST_FILES})
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