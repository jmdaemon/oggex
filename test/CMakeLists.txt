FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest"
    )
FetchContent_MakeAvailable(doctest)

set(RESOURCE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test/resources/")
set(DOCTEST_LIB "${OGGEX_SOURCE_DIR}/include/")

set(RESOURCE_FILES
  #resources/
  #resources/12727a5f30b1429a1fd35113fd2550d8.png
  resources/inputFile1.png
  )

set (DOCTEST_LIBRARY doctest_library)

add_executable(${DOCTEST_LIBRARY} doctest-main.cpp)

target_compile_features(${DOCTEST_LIBRARY} PRIVATE cxx_std_20)
#target_include_directories(${DOCTEST_LIBRARY} PUBLIC ${DOCTEST_INCLUDE_DIR}/doctest "${OGGEX_SOURCE_DIR}/include/" )
target_include_directories(${DOCTEST_LIBRARY} PUBLIC ${DOCTEST_LIB})
target_link_libraries(${DOCTEST_LIBRARY} PRIVATE image_library doctest)
#target_link_libraries(${DOCTEST_LIBRARY} PRIVATE image_library doctest::doctest)

add_subdirectory(image)
add_subdirectory(audio)
add_subdirectory(encoder)
#add_subdirectory(decoder)
