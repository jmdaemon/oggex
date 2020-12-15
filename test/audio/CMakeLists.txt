set (TARGET embed_audio)
add_executable(${TARGET} EmbedAudioTests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_20)
target_link_libraries(${TARGET} PRIVATE audio_library doctest)

target_include_directories(${TARGET} PUBLIC ${DOCTEST_INCLUDE_DIR} )

add_test(NAME testembedaudio COMMAND ${TARGET})
