# ================ Embed Audio Tests ================
set(EMBED_TESTS test-embed-audio)
make_test(
    NAME ${EMBED_TESTS}
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_LIB}
    SOURCES EmbedAudioTests.cpp
    DEPS fmt ${TESTS_MAIN} cmd file image audio_library audio)

set_target_properties(${EMBED_TESTS} PROPERTIES RESOURCE "${RESOURCE_FILES}")

# ================ Extract Audio Tests ================
set(EXTRACT_TESTS test-extract-audio)
make_test(
    NAME ${EXTRACT_TESTS}
    CSTANDARD ${CSTANDARD}
    HEADERS ${DOCTEST_LIB}
    SOURCES ExtractAudioTests.cpp
    DEPS fmt ${TESTS_MAIN} cmd file audio_library audio)

set_target_properties(${EXTRACT_TESTS} PROPERTIES RESOURCE "${RESOURCE_FILES}" )

# Copy test files to ${CMAKE_BINARY_DIR}
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")
