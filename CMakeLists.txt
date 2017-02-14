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

#
# QT5_CREATE_QRC(_qrc_file ...)
#
#   method will create a qrc file and dynamically populate it with files entered
#   as variable parameters to the function. each file will have an alias which will
#   equate to the file's name. user's are able to add a prefix as well as a language
#   for the resource.
#
#   LANG=""
#     language for which all the resources will belong to
#
#   PREFIX="/"
#     prefix path for which all files will belong to
#
#   _qrc_file  path to the qrc file you'de like to create
#      ...     list of files to add to qrc file
##
function(QT5_CREATE_QRC _qrc_file)

	# parse function arguments
	set(_options)
	set(_one_value_args LANG PREFIX)
	set(_multi_value_args)

	cmake_parse_arguments(_INPUT "${_options}" "${_one_value_args}" "${_multi_value_args}" ${ARGN})
	set(_files ${_INPUT_UNPARSED_ARGUMENTS})

	# qrc qresource xml attributes
	set(_lang_attr)
	if(_INPUT_LANG)
		set(_lang_attr " lang=\"${_INPUT_LANG}\"")
	endif()

	set(_prefix_attr)
	if(_INPUT_PREFIX)
		set(_prefix_attr " prefix=\"${_INPUT_PREFIX}\"")
	endif()

	# qrc file elements
	set(_file_elements)
	foreach(_file ${_files})
		get_filename_component(_filename ${_file} NAME)
		list(APPEND _file_elements "<file alias=\"${_filename}\">${_file}</file>")
	endforeach()

	# write qrc file
	set(_qrc_file_in "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${_qrc_file}.in")
	string(REPLACE ";" "\n\t\t" _file_elements "${_file_elements}")

	file(WRITE "${_qrc_file_in}"
"<RCC>
	<qresource@_lang_attr@@_prefix_attr@>
		@_file_elements@
	</qresource>
</RCC>"
	)

	configure_file("${_qrc_file_in}" "${_qrc_file}")

endfunction()

# custom command for i18n resource file
qt5_create_qrc(i18n.qrc ${QM_FILES} PREFIX "/i18n")

#add_custom_command(OUTPUT i18n.qrc
#	COMMAND
#	DEPENDS ${QM_FILES}
#)

# custom command for ui resource file
qt5_create_qrc(ui.qrc ${QML_FILES} PREFIX "/ui")
#add_custom_command(OUTPUT ui.qrc
#	COMMAND
#	DEPENDS ${QML_FILES}
#)

# executable
add_executable(application ${MAIN_FILE} ${SOURCE_FILES})  # TODO: include ${RCC_FILES}

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