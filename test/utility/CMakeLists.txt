# ================ Image Tests ================
make_test(
    NAME test-image
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES ImageTests.cpp
    DEPS fmt file image)
    #DEPS fmt image)

# ================ Audio Tests ================
make_test(
    NAME test-audio
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES AudioTests.cpp
    #DEPS fmt audio_library)
    DEPS fmt file audio_library)

 #set_property(test-audio testlib PROPERTY IMPORTED_LOCATION "/projectspath/LinkTest/TestLib/app/build/intermediates/cmake/debug/obj/armeabi-v7a/libtest-lib.so")

# ================ Command Tests ================
make_test(
    NAME test-cmd
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES CmdTests.cpp
    DEPS fmt cmd)

# ================ Masking Tests ================
make_test(
    NAME test-mask
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES MaskTests.cpp
    DEPS fmt file image audio_library audio)

# ================ Data Tests ================
make_test(
    NAME test-data
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_INCLUDE_DIR}
    SOURCES DataTests.cpp
    DEPS fmt file image audio_library audio)

# Copy test resources
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")
