set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")
#set(DOCTEST_LIB "${OGGEX_SOURCE_DIR}/include/")

set(RESOURCE_FILES
  resources/inputFile1.png
  resources/inputFile2.png
  resources/outputFile1.audio02.ogg
  )

# https://stackoverflow.com/questions/49413898/how-to-use-cmake-with-catch2
#set(TESTS_MAIN)
#set(TESTS_MAIN tests-main)
#add_library(${TESTS_MAIN} doctest.cpp)
#target_include_directories(${TESTS_MAIN} PUBLIC ${DOCTEST_INCLUDE_DIR})
#target_include_directories(${TARGET} PUBLIC ${DOCTEST_INCLUDE_DIR})

#set(TARGET tests)
#add_library(${TARGET} doctest_runner.cpp)
set(DOCTEST_RUNNER tests)
add_library(${DOCTEST_RUNNER} doctest_runner.cpp)
target_include_directories(${DOCTEST_RUNNER} PUBLIC ${DOCTEST_INCLUDE_DIR})
target_link_libraries(${DOCTEST_RUNNER})


#include(Doctest)
#include(${DOCTEST_INCLUDE_DIR}/scripts/cmake/doctest)
add_subdirectory(utility)
add_subdirectory(audio)

include(CTest)
include(${DOCTEST_SOURCE_DIR}/scripts/cmake/doctest.cmake)

#doctest_discover_tests(${TARGET})
