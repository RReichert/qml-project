# search for doxygen
find_package(Doxygen)

# run doxygen if available
if(${DOXYGEN_FOUND})

    # doxygen settings
    set(USE_MATHJAX "YES")
    set(DOXYGEN_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # doxygen configuration file
    configure_file(${DOXYGEN_CONFIG_FILE} ${DOXYGEN_FILE})

    # doxygen documentation compile
    add_custom_target(
        doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )

    # doxygen installation
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION doc)

endif()
