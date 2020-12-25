set(TARGET testimage)
add_executable(${TARGET} image-tests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_17)
target_link_libraries(${TARGET} PRIVATE image_library file_library doctest)

target_include_directories(${TARGET} PUBLIC ${DOCTEST_LIB})

add_test(NAME test_image COMMAND ${TARGET})
