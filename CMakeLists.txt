cmake_minimum_required(VERSION 3.12)

project(
    oggex 
    VERSION 1.5.0
    DESCRIPTION "Encode and decode ogg audio files in images" 
    LANGUAGES C CXX)

# Variable Toggles
set(NO_COLOR OFF CACHE INTERNAL "Toggles colored output errors")
set(BUILD_DOC ON CACHE INTERNAL "Build documentation")
set(ENABLE_LOGGING OFF CACHE INTERNAL "View the logging statements/debug info")
set(LOG_LEVEL 0 CACHE INTERNAL "Enable only specific log levels")

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with "
                        "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                        "remove CMakeCache.txt and CMakeFiles.")
endif()

# Include CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/" "${PROJECT_SOURCE_DIR}/cmake" )

if (NO_COLOR)
    # Don't use colored output
else()
    # Include colored output by default
    include(Color)
endif()

# Single source project version
configure_file(
  "${PROJECT_SOURCE_DIR}/include/Version.h.in"
  "${PROJECT_BINARY_DIR}/include/Version.h")

# Include dependencies

# CMake modules
include(FetchContent)
include(Utilities)
include(Library)

# Third Party Libraries
include(spdlog)
include(utility)
include(bytesize)
include(cnc)

# Specify project dependencies
# DEB_DEPENDS: Debian packages that provide the libraries the project depends upon
set(DEB_DEPENDS libc)

# Include header files
set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/include")
set(HEADERS_VERSION "${PROJECT_BINARY_DIR}/include")

# Add subdirectories
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(app)

if(BUILD_TESTING)
    include(doctest)
    include(MakeTests)
    include(CTest)
    add_subdirectory(test)
endif()

include(Install)

# Packages
include(InstallRequiredSystemLibraries)
include(Debian)
