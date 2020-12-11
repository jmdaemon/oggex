FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest"
    )
FetchContent_MakeAvailable(doctest)

set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")

add_executable(doctest_library doctest-main.cpp)

target_compile_features(doctest_library PRIVATE cxx_std_17)
target_include_directories(doctest_library PUBLIC ${DOCTEST_INCLUDE_DIR} )
target_link_libraries(doctest_library PRIVATE image_library doctest::doctest)

add_subdirectory(image)
add_subdirectory(encoder)
