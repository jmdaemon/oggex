cmake_minimum_required(VERSION 3.12)

project(
    oggex 
    VERSION 1.5.0
    DESCRIPTION "Encode and decode ogg audio files in images" 
    LANGUAGES CXX
    )

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) 
    set(CMAKE_CXX_STANDARD 20) 
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_STANDARD_REQUIRED ON) 
    set(CMAKE_CXX_EXTENSIONS OFF) 
    set_property(GLOBAL PROPERTY USE_FOLDERS ON) 
endif()

if (NOT COLOR)
    # Don't use colored output
else()
    # Include colored output by default
    include(Color)
endif()

# Build the application normally
# if not building for javascript
if(NOT $ENV{BUILD_JS})
    set($ENV{BUILD_JS} OFF)
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

# Single source project version
configure_file (
  "${PROJECT_SOURCE_DIR}/include/Version.h.in"
  "${PROJECT_BINARY_DIR}/include/Version.h"
)

# Include dependencies
include(FetchContent)
include(fmt)
include(doctest)
include(MakeLibrary)

# Set includes for libraries
set(CSTANDARD cxx_std_20)
set(INCLUDES_DIR "${OGGEX_SOURCE_DIR}/include")
set(UTILITY_DIR "${INCLUDES_DIR}/util")
set(AUDIO_DIR "${INCLUDES_DIR}/audio")

# Include subprojects

# Utility C Library
set(UTILITY_LIBP "${PROJECT_SOURCE_DIR}/subprojects/utility/build/release/lib")
set(UTILITY_LIBD "${PROJECT_SOURCE_DIR}/subprojects/utility")
set(UTILITY_SRCS "${UTILITY_LIBD}/src/file.c")
set(UTILITY_HEADERS "${PROJECT_SOURCE_DIR}/subprojects/utility/include")
set(UTILITY_LIB utility)

#add_library(${UTILITY_LIB} SHARED IMPORTED GLOBAL)
#set_target_properties(
    #${UTILITY_LIB}
    #PROPERTIES 
        #IMPORTED_LOCATION ${UTILITY_HEADERS}
        #IMPORTED_IMPLIB ${UTILITY_LIBP}/${UTILITY_LIB}.so
#)
#find_library(${UTILITY_LIB}
             #NAMES ${UTILITY_LIB}
             #HINTS ${UTILITY_LIBP})

find_library(${UTILITY_LIB}
    NAMES ${UTILITY_LIB} libutility
    HINTS ${UTILITY_LIBP} ${UTILITY_LIBD})

#include_directories(${UTILITY_HEADERS})

#add_library(${UTILITY_LIB} SHARED IMPORTED)
#set_target_properties(${UTILITY_LIB}
    #PROPERTIES IMPORTED_LOCATION ${UTILITY_LIBP}/lib${UTILITY_LIB}.so)

#add_library(${UTILITY_LIB} SHARED )
#target_sources(${UTILITY_LIB}
    #PRIVATE ${UTILITY_SRCS}
    #PUBLIC  ${UTILITY_HEADERS})

#target_include_directories(${UTILITY_LIB} PUBLIC ${UTILITY_HEADERS})
##target_link_libraries(${UTILITY_LIB})
##target_compile_features(${UTILITY_LIB})

#source_group(
    #TREE "${PROJECT_SOURCE_DIR}/include"
    #PREFIX "Header Files"
    #FILES ${UTILITY_HEADERS})

#if(NOT libutility)
  #message(FATAL_ERROR "Utility library not found!")
#endif()

#if(NOT ${UTILITY_LIB})
  #message(FATAL_ERROR "Utility library not found!")
#endif()

# Add subdirectories
#add_subdirectory(subprojects)
add_subdirectory(src)
if (NOT $ENV{BUILD_JS})
    add_subdirectory(app)
endif()

if(BUILD_TESTING)
    include(MakeTests)
    add_subdirectory(test)
    #include (CTest)
endif()

# Package for debian
include(Debian)

set(CMAKE_INSTALL_PREFIX /usr/local)
install(TARGETS ${OGGEX} DESTINATION bin)
install(TARGETS ${OGGEX} CONFIGURATIONS Debug   RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/Debug/bin)
install(TARGETS ${OGGEX} CONFIGURATIONS Release RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/Release/bin)

# Define Ninja uninstall
add_custom_target(uninstall COMMAND xargs rm < ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt)
