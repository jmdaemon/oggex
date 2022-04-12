set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")
#set(DOCTEST_LIB "${OGGEX_SOURCE_DIR}/include/")

set(RESOURCE_FILES
  resources/inputFile1.png
  resources/inputFile2.png
  resources/outputFile1.audio02.ogg
  )

# https://stackoverflow.com/questions/49413898/how-to-use-cmake-with-catch2
set(TARGET tests)
#set(TESTS_MAIN)
#set(TESTS_MAIN tests-main)
#add_library(${TESTS_MAIN} doctest.cpp)
#target_include_directories(${TESTS_MAIN} PUBLIC ${DOCTEST_INCLUDE_DIR})
add_executable(${TARGET} doctest.cpp)
target_include_directories(${TARGET} PUBLIC ${DOCTEST_INCLUDE_DIR})

#include(Doctest)
#include(${DOCTEST_INCLUDE_DIR}/scripts/cmake/doctest)
add_subdirectory(util)
add_subdirectory(audio)

include(CTest)
include(${DOCTEST_SOURCE_DIR}/scripts/cmake/doctest.cmake)

doctest_discover_tests(${TARGET})
