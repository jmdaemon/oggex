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
set(EXTRACT_AUDIO_TESTS extract-audio)
add_executable(${EXTRACT_AUDIO_TESTS} ExtractAudioTests.cpp)

target_compile_features(${EXTRACT_AUDIO_TESTS} PRIVATE cxx_std_20)
target_link_libraries(${EXTRACT_AUDIO_TESTS} PRIVATE fmt audio audio_library file_library cmd_library ${TESTS_MAIN})
target_include_directories(${EXTRACT_AUDIO_TESTS} PUBLIC ${DOCTEST_INCLUDE_DIR})
#FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")

set_target_properties(${EXTRACT_AUDIO_TESTS} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )

add_test(NAME test-extract-audio COMMAND ${EXTRACT_AUDIO_TESTS})

# Copy test files to ${CMAKE_BINARY_DIR}
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")
