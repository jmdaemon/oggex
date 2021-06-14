set(TARGET testextractaudio)
add_executable(${TARGET} ExtractAudioTests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_20)
target_link_libraries(${TARGET} PRIVATE audio audio_library file_library fmt doctest)

target_include_directories(${TARGET} PUBLIC ${DOCTEST_LIB})
FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")

set_target_properties(${TARGET} PROPERTIES
    RESOURCE "${RESOURCE_FILES}" )


add_test(NAME test_extractaudio COMMAND ${TARGET})
