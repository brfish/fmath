add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

macro(fmath_test)
    cmake_parse_arguments(
        FMATH_TEST
        ""
        "NAME"
        "SOURCES;LIBRARIES"
        ${ARGN}
    )
    add_executable(${FMATH_TEST_NAME} ${FMATH_TEST_SOURCES})

    target_link_libraries(${FMATH_TEST_NAME} gtest gmock gtest_main fmath::fmath ${FMATH_TEST_LIBRARIES})
    gtest_discover_tests(
        ${FMATH_TEST_NAME}
        WORKING_DIRECTORY
            ${PROJECT_DIR}
    )
    set_target_properties(${FMATH_TEST_NAME} PROPERTIES FOLDER test)
endmacro()