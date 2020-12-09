cmake_minimum_required(VERSION 3.10)

project(oggex VERSION 0.1.0 DESCRIPTION "Encode and decode ogg audio files in images" LANGUAGES CXX)

#set_target_property(oggex PROPERTIES VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set( OGGEX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( OGGEX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

configure_file (
  "${PROJECT_SOURCE_DIR}/oggex.hpp.in"
  "${PROJECT_BINARY_DIR}/oggex.hpp"
  #"${PROJECT_SOURCE_DIR}/oggex.h.in"
  #"${PROJECT_BINARY_DIR}/oggex.h"
  #"${PROJECT_SOURCE_DIR}/Image.hpp"
)#configure_file(src/encoder/main/ogg-encoder.hpp.in ogg-encoder.hpp)


find_package(OpenCV 4.5.0 REQUIRED)
include(FetchContent)
include_directories( include ${OpenCV_INCLUDE_DIRS} ${DOCTEST_INCLUDE_DIR} )

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
set ( ${OGGEX_DEFINITIONS} -Wno-dev)
add_definitions( ${OGGEX_DEFINITIONS} )
#add_subdirectory(src/encoder/main)
#add_subdirectory(src/image/main)

#find_package(OpenCV REQUIRED)
#set(OpenCV_DIR "/usr/local/include/opencv")
#include_directories( ${OpenCV_INCLUDE_DIRS} )

#configure_file(src/encoder/main/ogg-encoder.hpp.in src/encoder/main/ogg-encoder.hpp)
#include(FetchContent)

#FetchContent_Declare( 
    #opencv 
    #GIT_REPOSITORY https://github.com/opencv/opencv.git 
    #GIT_TAG        4.5.0
#)
#FetchContent_MakeAvailable(opencv)

#set(OpenCV_DIR ${CMAKE_CURRENT_BINARY_DIR})



#FetchContent_MakeAvailable(libogg)

#add_executable(ogg-encoder src/encoder/main/ogg-encoder.cpp)
#configure_file(src/encoder/main/ogg-encoder.hpp.in ogg-encoder.hpp)
#include_directories(${PROJECT_BINARY_BIN})

#add_executable(Image src/image/main/Image.cpp)
#configure_file(src/image/main/Image.hpp image.hpp)
#target_link_libraries(Image ${OpenCV_LIBS} ) 
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ) 
#target_include_directories(Image PUBLIC "${PROJECT_BINARY_DIR}")
#target_include_directories( ${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

#set(SOURCES test/image/main/image-tests.cpp ${include}/image.hpp)
#set(SOURCES test/image/main/image-tests.cpp include/image.hpp)

#set(IMAGE_SOURCE ${src/image/main}/Image.hpp)
#add_library(Image.hpp src/image/main/Image.cpp PRIVATE ${IMAGE_SOURCE})

#enable_testing()
#add_test("Test_Image_Class" test/image/main/image-tests.cpp )
#add_executable(image-tests test/image/main/image-tests.cpp)
#add_executable(image-tests test/image/main/image-tests.cpp ${IMAGE_SOURCE})
#target_link_libraries(image-tests PUBLIC ${DOCTEST_INCLUDE_DIR} ${SOURCES})

#add_executable(image-tests test/image/main/image-tests.cpp ${IMAGE_SOURCE})
#target_link_libraries(image-tests PUBLIC ${DOCTEST_INCLUDE_DIR})
#target_include_directories(image-tests PRIVATE ${IMAGE_SOURCE})
