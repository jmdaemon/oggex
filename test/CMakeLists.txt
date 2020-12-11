FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest"
    )
FetchContent_MakeAvailable(doctest)

set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")

#configure_file (
  #"${PROJECT_SOURCE_DIR}/resources.hpp.in"
  #"${PROJECT_BINARY_DIR}/resources.hpp"
#)
set(RESOURCE_FILES
  #resources/
  resources/12727a5f30b1429a1fd35113fd2550d8.png)

add_executable(doctest_library doctest-main.cpp)

target_compile_features(doctest_library PRIVATE cxx_std_17)
target_include_directories(doctest_library PUBLIC ${DOCTEST_INCLUDE_DIR} )
target_link_libraries(doctest_library PRIVATE image_library doctest::doctest)

add_subdirectory(image)
add_subdirectory(encoder)
