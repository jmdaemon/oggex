# ================ Image Tests ================
make_test(
    NAME test-image
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES ImageTests.cpp
    DEPS fmt ${TESTS_MAIN} file image)

# ================ Audio Tests ================
make_test(
    NAME test-audio
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES AudioTests.cpp
    DEPS fmt ${TESTS_MAIN} file audio_library audio)

# ================ Command Tests ================
make_test(
    NAME test-cmd
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_LIB}
    SOURCES CmdTests.cpp
    DEPS fmt ${TESTS_MAIN} cmd)

# ================ Masking Tests ================
make_test(
    NAME test-mask
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_LIB}
    SOURCES MaskTests.cpp
    DEPS fmt ${TESTS_MAIN} file image audio_library audio)

# ================ Data Tests ================
make_test(
    NAME test-data
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_LIB}
    SOURCES DataTests.cpp
    DEPS fmt ${TESTS_MAIN} file image audio_library audio)

# Copy test resources
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")
