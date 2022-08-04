cmake_minimum_required(VERSION 3.12)

project(
    oggex 
    VERSION 1.5.0
    DESCRIPTION "Encode and decode ogg audio files in images" 
    LANGUAGES C CXX)

if (NOT COLOR)
    # Don't use colored output
else()
    # Include colored output by default
    include(Color)
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
                        "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                        "remove CMakeCache.txt and CMakeFiles.")
endif()

set( OGGEX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( OGGEX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" "${PROJECT_SOURCE_DIR}/cmake" )

# Single source project version
configure_file (
  "${PROJECT_SOURCE_DIR}/include/Version.h.in"
  "${PROJECT_BINARY_DIR}/include/Version.h")

# Include dependencies
include(FetchContent)
include(Library)
include(Utilities)
include(fmt)
#include(doctest)
include(utility)
#include(logc)
include(bytesize)
include(cnc)

# Set includes for libraries
set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADERS_VERSION "${PROJECT_BINARY_DIR}/include")

set(CSTANDARD cxx_std_20)
#set(INCLUDES_DIR "${OGGEX_SOURCE_DIR}/include")
set(UTILITY_DIR "${INCLUDES_DIR}/utility")
set(AUDIO_DIR "${INCLUDES_DIR}/audio")

# Add subdirectories
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(app)

if(BUILD_TESTING)
    include(MakeTests)
    include(CTest)
    #add_subdirectory(test)
endif()

# Manual Installs
# Set default manual installation directory to /usr/local
set(CMAKE_INSTALL_PREFIX /usr/local)

# Manual Uninstall Target
# Usage:
# cmake uninstall .
# sudo make uninstall or sudo ninja uninstall
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)
endif()

if ((TARGET uninstall) AND (EXISTS "${LOC_PATH}"))
    message(FATAL_ERROR
        "You cannot uninstall in the source directory."
        "You may only uninstall from the build subdirectory."
        "Feel free to remove remove CMakeCache.txt and CMakeFiles.")
endif()

# Packages
include(InstallRequiredSystemLibraries)
include(Debian)

# Define more direct uninstall target
#add_custom_target(uninstall COMMAND xargs rm < ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt)
