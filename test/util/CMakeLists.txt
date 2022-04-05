function(make_test)
    # Set make_test arguments
    set(ARG_PREFIX TEST)
    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME CSTANDARD)
    set(_MULTI_VALUE_ARGS HEADERS SOURCES DEPS)
    cmake_parse_arguments(${ARG_PREFIX} "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    # Show make_tests arguments
    #message(STATUS "======================")
    #message(STATUS "make_library arguments: ${LIB_NAME}, followed by ${ARGN}")
    #message(STATUS "TEST_NAME: ${TEST_NAME}")
    #message(STATUS "TEST_CSTANDARD: ${TEST_CSTANDARD}")
    #message(STATUS "TEST_HEADERS: ${TEST_HEADERS}")
    #message(STATUS "TEST_SOURCES: ${TEST_SOURCES}")
    #message(STATUS "TEST_DEPS: ${TEST_DEPS}")
    #message(STATUS "======================")

    # Set TARGET
    # Creates test- prefix
    #set(${TARGET} "test-${TEST_NAME}")
    set(TARGET ${TEST_NAME})

    # Add tests
    add_executable(${TARGET} ${TEST_SOURCES})
    target_compile_features(${TARGET} PRIVATE ${TEST_CSTANDARD})
    target_link_libraries(${TARGET} PRIVATE ${TEST_DEPS})
    target_include_directories(${TARGET} PUBLIC ${TEST_HEADERS})
    add_test(NAME ${TARGET} COMMAND ${TARGET})
endfunction()

# ================ Image Tests ================
make_test(
    NAME test-image
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES ImageTests.cpp
    DEPS image file fmt ${TESTS_MAIN})

# ================ Audio Tests ================
make_test(
    NAME test-audio
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES AudioTests.cpp
    DEPS fmt "${TESTS_MAIN}" file audio_library audio)

# ================ Command Tests ================
set (CMD_TESTS test-cmd)
add_executable(${CMD_TESTS} CmdTests.cpp)
target_compile_features(${CMD_TESTS} PRIVATE cxx_std_20)

target_link_libraries(${CMD_TESTS} PRIVATE fmt cmd_library ${TESTS_MAIN})
target_include_directories(${CMD_TESTS} PUBLIC ${DOCTEST_LIB})
add_test(NAME test-cmd COMMAND ${CMD_TESTS})

# ================ Masking Tests ================
set (MASK_TESTS test-mask)
add_executable(${MASK_TESTS} MaskTests.cpp)
target_compile_features(${MASK_TESTS} PRIVATE cxx_std_20)

target_link_libraries(${MASK_TESTS} PRIVATE audio_library image_library file_library fmt ${TESTS_MAIN})
target_include_directories(${MASK_TESTS} PUBLIC ${DOCTEST_LIB})
add_test(NAME test-mask COMMAND ${MASK_TESTS})

# ================ Data Tests ================
set (DATA_TESTS test-data)
add_executable(${DATA_TESTS} DataTests.cpp)
target_compile_features(${DATA_TESTS} PRIVATE cxx_std_20)

target_link_libraries(${DATA_TESTS} PRIVATE audio_library image_library file_library fmt ${TESTS_MAIN})
target_include_directories(${DATA_TESTS} PUBLIC ${DOCTEST_LIB})
add_test(NAME test-data COMMAND ${DATA_TESTS})

FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")
