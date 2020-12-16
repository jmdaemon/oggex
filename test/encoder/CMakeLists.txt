set(TARGET test-ogg-encoder)
add_executable(${TARGET} ogg-encoder-tests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_17)
target_link_libraries(${TARGET} PRIVATE image_library doctest)
target_include_directories(${TARGET} PUBLIC ${DOCTEST_INCLUDE_DIR} ) 

set_target_properties(${TARGET} PROPERTIES
    RESOURCE "${RESOURCE_FILES}")

add_test(NAME test_encoder COMMAND ${TARGET})
