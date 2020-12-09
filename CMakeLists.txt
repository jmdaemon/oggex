cmake_minimum_required(VERSION 3.5)

project(oggex VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(src/encoder/main)
#add_subdirectory(src/image/main)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(Image src/image/main/Image.cpp)
target_link_libraries(Image ${OpenCV_LIBS} ) 

add_executable(ogg-encoder src/encoder/main/ogg-encoder.cpp)
#configure_file(src/encoder/main/ogg-encoder.hpp.in src/encoder/main/ogg-encoder.hpp)
configure_file(src/encoder/main/ogg-encoder.hpp.in ogg-encoder.hpp)

include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY "https://github.com/onqtam/doctest")
    #GIT_TAG         2.4.1
FetchContent_MakeAvailable(doctest)
FetchContent_Declare(
    libogg
    GIT_REPOSITORY "https://github.com/xiph/ogg")
FetchContent_MakeAvailable(libogg)



#add_executable(encoder 
