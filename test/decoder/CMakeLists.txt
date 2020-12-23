set(TARGET testextractaudio)
add_executable(${TARGET} ExtractAudioTests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_20)
target_link_libraries(${TARGET} PRIVATE audio_library doctest)

target_include_directories(${TARGET} PUBLIC ${DOCTEST_LIB})

add_test(NAME test_extractaudio COMMAND ${TARGET})
