set (EMBED_AUDIO_TESTS embed_audio)
set (CMD_TESTS testcmd)
set (HASH_TESTS testhash)
set (AUDIO_TESTS testaudio)

add_executable(${EMBED_AUDIO_TESTS} EmbedAudioTests.cpp)
add_executable(${CMD_TESTS} CmdTests.cpp)
add_executable(${HASH_TESTS} HashTests.cpp)
add_executable(${AUDIO_TESTS} AudioTests.cpp)

target_compile_features(${EMBED_AUDIO_TESTS} PRIVATE cxx_std_20)
target_compile_features(${CMD_TESTS} PRIVATE cxx_std_20)
target_compile_features(${HASH_TESTS} PRIVATE cxx_std_20)
target_compile_features(${AUDIO_TESTS} PRIVATE cxx_std_20)

target_link_libraries(${EMBED_AUDIO_TESTS} PRIVATE audio_library image_library file_library fmt doctest)
target_link_libraries(${CMD_TESTS} PRIVATE audio_library image_library file_library fmt doctest)
target_link_libraries(${HASH_TESTS} PRIVATE audio_library image_library file_library fmt doctest)
target_link_libraries(${AUDIO_TESTS} PRIVATE audio_library file_library fmt doctest)

target_include_directories(${EMBED_AUDIO_TESTS} PUBLIC ${DOCTEST_LIB})
target_include_directories(${CMD_TESTS} PUBLIC ${DOCTEST_LIB})
target_include_directories(${HASH_TESTS} PUBLIC ${DOCTEST_LIB})
target_include_directories(${AUDIO_TESTS} PUBLIC ${DOCTEST_LIB})

FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")

set_target_properties(${EMBED_AUDIO_TESTS} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )

add_test(NAME test_embedaudio COMMAND ${EMBED_AUDIO_TESTS})
add_test(NAME test_cmd COMMAND ${CMD_TESTS})
add_test(NAME test_hash COMMAND ${HASH_TESTS})
add_test(NAME test_audio COMMAND ${AUDIO_TESTS})
