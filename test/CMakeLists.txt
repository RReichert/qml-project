# unit test files
set(TEST_FILES )

# find google test
find_package(GTest)

# build run_tests if gtest is available
if(GTest_FOUND)

    # unit test compilation
    add_executable(run_tests ${TEST_FILE} basic_test.cpp)
    target_link_libraries(run_tests ${GTEST_BOTH_LIBRARIES})
    target_include_directories(run_tests PUBLIC ${GTEST_INCLUDE_DIRS})

    # unit test installation
    install(
        TARGETS run_tests
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
    )

endif()