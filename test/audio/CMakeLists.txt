# ================ Embed Audio Tests ================
set (EMBED_AUDIO_TESTS embed_audio)
add_executable(${EMBED_AUDIO_TESTS} EmbedAudioTests.cpp)

target_compile_features(${EMBED_AUDIO_TESTS} PRIVATE cxx_std_20)
target_link_libraries(${EMBED_AUDIO_TESTS} PRIVATE audio audio_library image_library file_library fmt doctest)
target_include_directories(${EMBED_AUDIO_TESTS} PUBLIC ${DOCTEST_LIB})

set_target_properties(${EMBED_AUDIO_TESTS} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )

add_test(NAME test_embedaudio COMMAND ${EMBED_AUDIO_TESTS})

# ================ Extract Audio Tests ================
set(EXTRACT_AUDIO_TESTS testextractaudio)
add_executable(${EXTRACT_AUDIO_TESTS} ExtractAudioTests.cpp)

target_compile_features(${EXTRACT_AUDIO_TESTS} PRIVATE cxx_std_20)
target_link_libraries(${EXTRACT_AUDIO_TESTS} PRIVATE audio audio_library file_library fmt doctest)
target_include_directories(${EXTRACT_AUDIO_TESTS} PUBLIC ${DOCTEST_LIB})

#FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")

set_target_properties(${EXTRACT_AUDIO_TESTS} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )

add_test(NAME test_extractaudio COMMAND ${EXTRACT_AUDIO_TESTS})

# Copy test files to ${CMAKE_BINARY_DIR}
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")
