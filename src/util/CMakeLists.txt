# Utility functions for creating library modules

include(CMakeParseArguments)
function(make_library)
    # Arguments:
    #LIB_NAME    # Name of the library target
    #LIB_TYPE    # Type of the library to build
    #LIB_HEADERS # Library headers
    #LIB_SOURCES # Library sources
    #LIB_DEPS    # Library dependencies

    # Set make_library arguments
    set(ARG_PREFIX LIB)
    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME TYPE)
    set(_MULTI_VALUE_ARGS HEADERS SOURCES DEPS)
    cmake_parse_arguments(${ARG_PREFIX} "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    # Show make_library arguments
    #message(STATUS "======================")
    #message(STATUS "make_library arguments: ${LIB_NAME}, followed by ${ARGN}")
    #message(STATUS "LIB_NAME: ${LIB_NAME}")
    #message(STATUS "LIB_TYPE: ${LIB_TYPE}")
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
    target_compile_features(${TARGET} PUBLIC cxx_std_20)

    source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${LIB_HEADERS})
endfunction()

function(make_static_shared_lib)
    # Set make_library arguments
    set(ARG_PREFIX LIB)
    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME)
    set(_MULTI_VALUE_ARGS HEADERS SOURCES DEPS)
    cmake_parse_arguments(${ARG_PREFIX} "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    make_library(
        NAME ${LIB_NAME}
        TYPE shared
        HEADERS "${OGGEX_SOURCE_DIR}/include/util"
        SOURCES "${FILE_SRCS}"
        DEPS "${FILE_DEPS}")

    make_library(
        NAME ${LIB_NAME}
        TYPE static
        HEADERS "${LIB_HEADERS}"
        SOURCES "${LIB_SOURCES}"
        DEPS "${LIB_DEPS}")
endfunction()

# ================ File Library ================
set(FILE_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(FILE_SRCS File.cpp)
set(FILE_DEPS fmt)

# Add both shared and static library targets
make_static_shared_lib(
    NAME files
    HEADERS "${OGGEX_SOURCE_DIR}/include/util"
    SOURCES "${FILE_SRCS}"
    DEPS "${FILE_DEPS}")
#make_library(
    #NAME files
    #TYPE shared
    #HEADERS "${OGGEX_SOURCE_DIR}/include/util"
    #SOURCES "${FILE_SRCS}"
    #DEPS "${FILE_DEPS}")

#make_library(
    #NAME files
    #TYPE static
    #HEADERS "${FILE_HEADERS}"
    #SOURCES "${FILE_SRCS}"
    #DEPS "${FILE_DEPS}")


# ================ Image Library ================
set(IMAGE_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(IMAGE_SRCS Image.cpp)
set(IMAGE_DEPS fmt)

make_library(
    NAME image
    TYPE shared
    HEADERS ${IMAGE_HEADERS}
    SOURCES ${IMAGE_SRCS}
    DEPS ${IMAGE_DEPS})

make_library(
    NAME image
    TYPE static
    HEADERS ${IMAGE_HEADERS}
    SOURCES ${IMAGE_SRCS}
    DEPS ${IMAGE_DEPS})


#set(TARGET image_library)

#add_library(${TARGET})
#target_sources(${TARGET}
    #PRIVATE Image.cpp 
    #PUBLIC  ${IMAGE_LIBRARY_HEADERS}
#)

#target_include_directories(${TARGET} PUBLIC ${IMAGE_LIBRARY_HEADERS})
#target_link_libraries(${TARGET} PRIVATE fmt)
#target_compile_features(${TARGET} PUBLIC cxx_std_11)

#source_group(
  #TREE "${PROJECT_SOURCE_DIR}/include"
  #PREFIX "Header Files"
  #FILES ${IMAGE_LIBRARY_HEADERS})

# ================ Audio Library ================
set(AUDIO_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET audio_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE Audio.cpp
    PRIVATE Mask.cpp
    PUBLIC  ${AUDIO_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${AUDIO_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt image_library)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${AUDIO_LIBRARY_HEADERS})

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

