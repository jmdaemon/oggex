cmake_minimum_required(VERSION 3.19) # CMake 3.9

project(
    oggex 
    VERSION 0.1.0 
    DESCRIPTION "Encode and decode ogg audio files in images" 
    LANGUAGES CXX
    )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) 
    set(CMAKE_CXX_STANDARD 20) 
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_STANDARD_REQUIRED True) 
    set(CMAKE_CXX_EXTENSIONS OFF) 
    set_property(GLOBAL PROPERTY USE_FOLDERS ON) 
    include(CTest) 
endif()

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
                        "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                        "remove CMakeCache.txt and CMakeFiles.")
endif()

set( OGGEX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( OGGEX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" "${PROJECT_SOURCE_DIR}/cmake" )

set( GLADE_FILES resources/xml/gtk3/ )

configure_file (
  "${PROJECT_SOURCE_DIR}/oggex.hpp.in"
  "${PROJECT_BINARY_DIR}/oggex.hpp"
)

include(FetchContent)

FetchContent_Declare(
    libfmt
    GIT_REPOSITORY "https://github.com/fmtlib/fmt")
FetchContent_MakeAvailable(libfmt)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-3.0)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

add_subdirectory(src)
add_subdirectory(app)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
