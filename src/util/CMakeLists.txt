# Utility functions for creating library modules

include(CMakeParseArguments)
function(make_library)
    # Arguments:
    #LIB_NAME       # Name of the library target
    #LIB_TYPE       # Type of the library to build
    #LIB_CSTANDARD  # CXX Standard
    #LIB_HEADERS    # Library headers
    #LIB_SOURCES    # Library sources
    #LIB_DEPS       # Library dependencies

    # Set make_library arguments
    set(ARG_PREFIX LIB)
    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME TYPE CSTANDARD)
    set(_MULTI_VALUE_ARGS HEADERS SOURCES DEPS)
    cmake_parse_arguments(${ARG_PREFIX} "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    # Show make_library arguments
    #message(STATUS "======================")
    #message(STATUS "make_library arguments: ${LIB_NAME}, followed by ${ARGN}")
    #message(STATUS "LIB_NAME: ${LIB_NAME}")
    #message(STATUS "LIB_TYPE: ${LIB_TYPE}")
    #message(STATUS "LIB_CSTANDARD: ${LIB_CSTANDARD")
    #message(STATUS "LIB_HEADERS: ${LIB_HEADERS}")
    #message(STATUS "LIB_SOURCES: ${LIB_SOURCES}")
    #message(STATUS "LIB_DEPS: ${LIB_DEPS}")
    #message(STATUS "======================")

    if(${LIB_TYPE} STREQUAL "static")
        # Build a static library
        set(TARGET ${LIB_NAME}_static)
    else()
        # Build a shared library by default
        set(TARGET ${LIB_NAME})
    endif()
    add_library(${TARGET})

    # Set sources
    target_sources(${TARGET}
        PRIVATE ${LIB_SOURCES}
        PUBLIC  ${LIB_HEADERS})

    target_include_directories(${TARGET} PUBLIC ${LIB_HEADERS})
    target_link_libraries(${TARGET} PRIVATE ${LIB_DEPS})
    target_compile_features(${TARGET} PUBLIC ${LIB_CSTANDARD})

    source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${LIB_HEADERS})
endfunction()

function(make_static_shared_lib)
    # Set arguments
    set(ARG_PREFIX LIB)
    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME CSTANDARD)
    set(_MULTI_VALUE_ARGS HEADERS SOURCES DEPS)
    cmake_parse_arguments(${ARG_PREFIX} "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    make_library(
        NAME "${LIB_NAME}"
        TYPE shared
        CSTANDARD "${LIB_CSTANDARD}"
        HEADERS "${LIB_HEADERS}"
        SOURCES "${LIB_SOURCES}"
        DEPS "${LIB_DEPS}")

    make_library(
        NAME "${LIB_NAME}"
        TYPE static
        CSTANDARD "${LIB_CSTANDARD}"
        HEADERS "${LIB_HEADERS}"
        SOURCES "${LIB_SOURCES}"
        DEPS "${LIB_DEPS}")
endfunction()

set(CSTANDARD cxx_std_20)
set(INCLUDES_DIR "${OGGEX_SOURCE_DIR}/include")
set(UTILITY_DIR "${INCLUDES_DIR}/util")
set(AUDIO_DIR "${INCLUDES_DIR}/audio")

# ================ File Library ================
# Add both shared and static library targets
make_static_shared_lib(
    NAME file
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR}
    SOURCES File.cpp
    DEPS fmt)

# ================ Image Library ================
make_static_shared_lib(
    NAME image
    CSTANDARD cxx_std_11
    HEADERS ${UTILITY_DIR}
    SOURCES Image.cpp
    DEPS fmt)

# ================ Audio Library ================
make_static_shared_lib(
    NAME audio_library
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Audio.cpp Mask.cpp
    DEPS fmt image)

# ================ Command Library ================
set(CMD_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET cmd_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE Data.cpp
    PRIVATE Cmd.cpp
    PRIVATE InputParser.cpp
    PUBLIC  ${CMD_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${CMD_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${CMD_LIBRARY_HEADERS})

