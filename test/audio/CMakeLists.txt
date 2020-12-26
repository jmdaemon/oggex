set (EMBED_AUDIO_TESTS embed_audio)
set (CMD_TESTS testcmd)

add_executable(${EMBED_AUDIO_TESTS} EmbedAudioTests.cpp)
add_executable(${CMD_TESTS} CmdTests.cpp)

target_compile_features(${EMBED_AUDIO_TESTS} PRIVATE cxx_std_20)
target_compile_features(${CMD_TESTS} PRIVATE cxx_std_20)

target_link_libraries(${EMBED_AUDIO_TESTS} PRIVATE audio_library image_library file_library fmt doctest)
target_link_libraries(${CMD_TESTS} PRIVATE audio_library image_library file_library fmt doctest)

#target_include_directories(${EMBED_AUDIO_TESTS} PUBLIC ${DOCTEST_LIB} ${HEADER_LIST})
target_include_directories(${EMBED_AUDIO_TESTS} PUBLIC ${DOCTEST_LIB})
target_include_directories(${CMD_TESTS} PUBLIC ${DOCTEST_LIB})

FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")

set_target_properties(${EMBED_AUDIO_TESTS} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )

add_test(NAME test_embedaudio COMMAND ${EMBED_AUDIO_TESTS})
add_test(NAME test_cmd COMMAND ${CMD_TESTS})
