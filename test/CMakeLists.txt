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
  resources/inputFile2.png
  resources/outputFile1.audio02.ogg
  )

set (DOCTEST_MAIN doctest_library)

add_executable(${DOCTEST_MAIN} doctest-main.cpp)
target_compile_features(${DOCTEST_MAIN} PRIVATE cxx_std_20)
target_include_directories(${DOCTEST_MAIN} PUBLIC ${DOCTEST_LIB})
target_link_libraries(${DOCTEST_MAIN} PRIVATE image_library doctest)

add_subdirectory(image)
add_subdirectory(audio)
add_subdirectory(extract)
