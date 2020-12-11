add_executable(testimage image-tests.cpp)

target_compile_features(testimage PRIVATE cxx_std_17)
target_link_libraries(testimage PRIVATE image_library doctest)
#target_link_libraries(testimage PRIVATE image_library doctest::doctest)
#target_link_libraries(testimage PRIVATE image_library ${DOCTEST_INCLUDE_DIR})

target_include_directories(testimage PUBLIC ${DOCTEST_INCLUDE_DIR} )

add_test(NAME testimagetest COMMAND testimage)
