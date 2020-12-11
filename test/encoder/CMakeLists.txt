add_executable(test-ogg-encoder ogg-encoder-tests.cpp)

target_compile_features(test-ogg-encoder PRIVATE cxx_std_17)
target_link_libraries(test-ogg-encoder PRIVATE image_library doctest)
target_include_directories(test-ogg-encoder PUBLIC ${DOCTEST_INCLUDE_DIR} ) 

set_target_properties(test-ogg-encoder PROPERTIES
    RESOURCE "${RESOURCE_FILES}")

add_test(NAME testencodertest COMMAND test-ogg-encoder)
