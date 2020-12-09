cmake_minimum_required(VERSION 3.19)

cmake_policy(SET CMP0048 NEW)
project(oggex VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(src/encoder/main)
#add_subdirectory(src/image/main)

#find_package(OpenCV REQUIRED)
#set(OpenCV_DIR "/usr/local/include/opencv")
#include_directories( ${OpenCV_INCLUDE_DIRS} )

#configure_file(src/encoder/main/ogg-encoder.hpp.in src/encoder/main/ogg-encoder.hpp)
include(FetchContent)

#FetchContent_Declare( 
    #opencv 
    #GIT_REPOSITORY https://github.com/opencv/opencv.git 
    #GIT_TAG        4.5.0
#)
#FetchContent_MakeAvailable(opencv)

#set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(OpenCV 4.5.0 REQUIRED)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest")
    #GIT_TAG         2.4.1
FetchContent_MakeAvailable(doctest)
#find_package(doctest 2.4.1 REQUIRED)
include_directories(${DOCTEST_INCLUDE_DIR})

FetchContent_Declare(
    libogg
    GIT_REPOSITORY "https://github.com/xiph/ogg")
FetchContent_MakeAvailable(libogg)

add_executable(ogg-encoder src/encoder/main/ogg-encoder.cpp)
configure_file(src/encoder/main/ogg-encoder.hpp.in ogg-encoder.hpp)
#include_directories(${PROJECT_BINARY_BIN})

add_executable(Image src/image/main/Image.cpp)
configure_file(src/image/main/image.hpp image.hpp)
target_link_libraries(Image ${OpenCV_LIBS} ) 
target_include_directories(Image PUBLIC "${PROJECT_BINARY_DIR}")


enable_testing()
add_test("Test_Image_Class" test/image/main/image-tests.cpp )
add_executable(image-tests test/image/main/image-tests.cpp)
target_link_libraries(image-tests PUBLIC ${DOCTEST_INCLUDE_DIR})
