# Unit Tests
set(HEADERS ${INCLUDES_DIR} ${DOCTEST_INCLUDE_DIR} ${jolly_SOURCE_DIR}/include ${utility_SOURCE_DIR}/include)
set(TARGET oggex)

file(COPY ../LICENSE DESTINATION ${CMAKE_BINARY_DIR})

# Configure binary paths for integration tests
set(OGGEX_BIN ../../app/oggex)
set(OGGEX_GTK ../../app/gtk/src/oggex-gtk)
set(OGGEX_QT ../../app/qt/oggex-qt)
configure_file(
  "${PROJECT_SOURCE_DIR}/test/oggex_int.h.in"
  "${PROJECT_BINARY_DIR}/test/oggex_int.h")
set(HEADERS ${HEADERS} ${PROJECT_BINARY_DIR}/test)

# Add unit tests
set(TEST_NAME test-${TARGET})
add_executable(${TEST_NAME} test_oggex.cpp)
target_include_directories(${TEST_NAME} PUBLIC ${HEADERS})
target_link_libraries(${TEST_NAME} PRIVATE ${PKG_DEPENDS} doctest oggex cli)
add_test(
    NAME ${TEST_NAME}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMAND ${TEST_NAME})

# Add integration tests
set(TEST_NAME test-oggex-int)
add_executable(${TEST_NAME} test_oggex_int.cpp)
target_include_directories(${TEST_NAME} PUBLIC ${HEADERS})
target_link_libraries(${TEST_NAME} PRIVATE ${PKG_DEPENDS} doctest oggex cli)
add_test(
    NAME ${TEST_NAME}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMAND ${TEST_NAME})

if (DISCOVER_TESTS)
    # Include doctest cmake module
    include(${DOCTEST_SOURCE_DIR}/scripts/cmake/doctest.cmake)

    # Discover unit tests
    doctest_discover_tests(${TEST_NAME})
endif()
