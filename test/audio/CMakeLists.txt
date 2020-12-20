set (TARGET embed_audio)
add_executable(${TARGET} EmbedAudioTests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_20)
target_link_libraries(${TARGET} PRIVATE audio_library fmt doctest)
target_include_directories(${TARGET} PUBLIC ${DOCTEST_LIB} )
#FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}/test/audio")
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")

set_target_properties(${TARGET} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )

add_test(NAME test_embedaudio COMMAND ${TARGET})
