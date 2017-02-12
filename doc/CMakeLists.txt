# project name
project(documentation)

# package configuration
find_package(Doxygen)

# enable documentation target if doxygen is available
if(DOXYGEN_FOUND)

    # documentation configuration settings
    set(USE_MATHJAX "YES")
    set(DOXYGEN_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # documentation configuration file
    configure_file(${DOXYGEN_CONFIG_FILE} ${DOXYGEN_FILE})

    # documentation compile
    add_custom_target(
        ${PROJECT_NAME}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )

    # documentation installation
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION doc)

endif()
