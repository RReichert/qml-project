# project
project(qt5-create-qrc)

# package configuration
find_package(Boost REQUIRED COMPONENTS filesystem program_options system)

# find external libraries/binaries
set(SOURCE_FILES main.cpp parse_command_line.cpp parse_command_line.h)

# executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

# installation
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)