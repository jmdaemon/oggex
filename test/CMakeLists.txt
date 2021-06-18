set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")
set(DOCTEST_LIB "${OGGEX_SOURCE_DIR}/include/")

set(RESOURCE_FILES
  #resources/
  #resources/12727a5f30b1429a1fd35113fd2550d8.png
  resources/inputFile1.png
  resources/inputFile2.png
  resources/outputFile1.audio02.ogg
  )

# https://stackoverflow.com/questions/49413898/how-to-use-cmake-with-catch2
set(TESTS_MAIN tests-main)
add_library(${TESTS_MAIN} doctest.cpp)
target_include_directories(${TESTS_MAIN} PUBLIC ${DOCTEST_INCLUDE_DIR})

add_subdirectory(util)
add_subdirectory(audio)
