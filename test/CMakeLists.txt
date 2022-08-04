set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")
#set(DOCTEST_LIB "${OGGEX_SOURCE_DIR}/include/")

set(RESOURCE_FILES
  resources/inputFile1.png
  resources/inputFile2.png
  resources/outputFile1.audio02.ogg
  )

# Oggex Tests
# ================ Embed Audio Tests ================

set(HEADERS ${INCLUDES_DIR} ${INCLUDES_DIR}/utility)
set(TARGET test-oggex)

# Add tests
add_executable(${TARGET} test_oggex.cpp)
#target_compile_features(${TARGET} PRIVATE ${TEST_CSTANDARD})
#target_include_directories(${TARGET} PUBLIC ${TEST_HEADERS})
target_include_directories(${TARGET} PUBLIC ${HEADERS} ${DOCTEST_INCLUDE_DIR})
target_link_libraries(${TARGET} PRIVATE
    fmt doctest cmd file image audio oggex)
add_test(NAME ${TARGET} COMMAND ${TARGET})

#make_test(
    #NAME ${TEST}
    #CSTANDARD ${CSTANDARD}
    #HEADERS ${DOCTEST_INCLUDE_DIR}
    #SOURCES test_oggex.cpp
    ##DEPS fmt ${DOCTEST_RUNNER} cmd file image audio sound)
    #DEPS fmt doctest cmd file image audio sound)


#make_test(
    #NAME ${EMBED_TESTS}
    #CSTANDARD ${CSTANDARD}
    #HEADERS ${DOCTEST_INCLUDE_DIR}
    #SOURCES EmbedAudioTests.cpp
    #DEPS fmt ${DOCTEST_RUNNER} cmd file image audio sound)

#set_target_properties(${EMBED_TESTS} PROPERTIES RESOURCE "${RESOURCE_FILES}")

## ================ Extract Audio Tests ================
#set(EXTRACT_TESTS test-extract-audio)
#make_test(
    #NAME ${EXTRACT_TESTS}
    #CSTANDARD ${CSTANDARD}
    #HEADERS ${DOCTEST_INCLUDE_DIR}
    #SOURCES ExtractAudioTests.cpp
    #DEPS fmt ${DOCTEST_RUNNER} cmd file audio sound)

#set_target_properties(${EXTRACT_TESTS} PROPERTIES RESOURCE "${RESOURCE_FILES}" )

# Copy test files to ${CMAKE_BINARY_DIR}
#FILE(COPY "../resources/inputFile1.png" DESTINATION "${CMAKE_BINARY_DIR}")
#FILE(COPY "../resources/inputFile2.png" DESTINATION "${CMAKE_BINARY_DIR}")
#FILE(COPY "../resources/outputFile1.audio02.ogg" DESTINATION "${CMAKE_BINARY_DIR}")



# https://stackoverflow.com/questions/49413898/how-to-use-cmake-with-catch2
#set(TESTS_MAIN)
#set(TESTS_MAIN tests-main)
#add_library(${TESTS_MAIN} doctest.cpp)
#target_include_directories(${TESTS_MAIN} PUBLIC ${DOCTEST_INCLUDE_DIR})
#target_include_directories(${TARGET} PUBLIC ${DOCTEST_INCLUDE_DIR})

#set(TARGET tests)
#add_library(${TARGET} doctest_runner.cpp)

set(DOCTEST_RUNNER tests)
add_library(${DOCTEST_RUNNER} SHARED doctest_runner.cpp)
target_include_directories(${DOCTEST_RUNNER} PUBLIC ${DOCTEST_INCLUDE_DIR})
#target_link_libraries(${DOCTEST_RUNNER} PUBLIC doctest)
#target_link_libraries(${DOCTEST_RUNNER} PUBLIC doctest::doctest)
target_link_libraries(${DOCTEST_RUNNER} PUBLIC doctest)


#include(Doctest)
#include(${DOCTEST_INCLUDE_DIR}/scripts/cmake/doctest)
#add_subdirectory(utility)
#add_subdirectory(audio)

#include(CTest)
#include(${DOCTEST_SOURCE_DIR}/scripts/cmake/doctest.cmake)
include(${DOCTEST_SOURCE_DIR}/scripts/cmake/doctest.cmake)

#doctest_discover_tests(${TARGET})
#doctest_discover_tests(${TARGET}
    #TEST_SUFFIX TESTS
    #WORKING_DIRECTORY ./)
