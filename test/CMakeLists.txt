# project name
project(unit-tests)

# package configurations
find_package(GTest)

# enable unit test target if gtest is available
if(GTest_FOUND)

    # unit test files
    set(TEST_FILES basic_test.cpp)

    # unit tests compile
    add_executable(${PROJECT_NAME} ${TEST_FILES})
    target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIRS})

    # unit tests installation
    install(
        TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
    )

endif()