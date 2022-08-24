# Unit Tests
set(HEADERS ${INCLUDES_DIR})
set(TARGET test-oggex)

# Add oggex tests
add_executable(${TARGET} test_oggex.cpp)
target_include_directories(${TARGET} PUBLIC ${HEADERS} ${DOCTEST_INCLUDE_DIR})
target_link_libraries(${TARGET} PRIVATE ${PKG_DEPENDS} cli oggex)
#add_test(NAME ${TARGET} COMMAND ${TARGET})

# Doctest discover tests

# Include cmake module
include(${DOCTEST_SOURCE_DIR}/scripts/cmake/doctest.cmake)

# Discover unit tests
doctest_discover_tests(${TARGET}
    TEST_PREFIX TEST
    WORKING_DIRECTORY ./)

