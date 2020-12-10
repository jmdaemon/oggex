cmake_minimum_required(VERSION 3.10)

project(oggex VERSION 0.1.0 DESCRIPTION "Encode and decode ogg audio files in images" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set( OGGEX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( OGGEX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )
set( SRC_LIBS   ${OpenCV_INCLUDE_DIRS} )
set( TEST_LIBS  ${DOCTEST_INCLUDE_DIR} )

set ( ${OGGEX_DEFINITIONS} -Wno-dev )
add_definitions( ${OGGEX_DEFINITIONS} )

configure_file (
  "${PROJECT_SOURCE_DIR}/oggex.hpp.in"
  "${PROJECT_BINARY_DIR}/oggex.hpp"
  #"${PROJECT_SOURCE_DIR}/src/image/main/Image.hpp"
)

find_package(OpenCV 4.5.0 REQUIRED)
include(FetchContent)
#include_directories( include ${OpenCV_INCLUDE_DIRS} ${DOCTEST_INCLUDE_DIR} )
include_directories( include ${LIBS} )

#FetchContent_Declare( 
    #opencv 
    #GIT_REPOSITORY https://github.com/opencv/opencv.git 
    #GIT_TAG        4.5.0
#)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest")
FetchContent_Declare(
    libogg
    GIT_REPOSITORY "https://github.com/xiph/ogg")
FetchContent_MakeAvailable(doctest libogg)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
    "${CMAKE_SOURCE_DIR}/CMake/modules/" )

set ( OGGEX_SOURCES
    src/encoder/main/ogg-encoder.cpp
    #src/decoder/main/ogg-decoder.cpp
    src/image/main/Image.cpp
    )

add_executable( ${PROJECT_NAME} ${OGGEX_SOURCES} )

target_link_libraries( ${PROJECT_NAME} ${LIBS} )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" )

target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} )
