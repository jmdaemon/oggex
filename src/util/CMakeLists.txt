# Utility functions for creating library modules

function(SET_HEADERS LIBRARY_HEADERS)
    set(LIBRARY_HEADERS ${LIBRARY_HEADERS} PARENT_SCOPE)
endfunction()

#function(SET_SHARED_TARGET LIBNAME)
    #set(TARGET_SHARED LIBNAME PARENT_SCOPE)
#endfunction()

#function(SET_STATIC_TARGET LIBNAME)
    #set(TARGET_STATIC LIBNAME PARENT_SCOPE)
#endfunction()

#function(MAKE_LIBRARY LIB_NAME LIB_TYPE LIB_HEADERS LIB_SOURCES LIB_DEPS)
#function(MAKE_LIBRARY)
#function(make_library)
include(CMakeParseArguments)
function(make_library)
    #set(${LIBNAME}      "Name of the library" PARENT_SCOPE)
    #set(${LIB_TYPE}     "Type of the library to make" PARENT_SCOPE)
    #set(${LIB_HEADERS}  "Library headers" PARENT_SCOPE)
    #set(${LIB_SOURCES}  "Library sources" PARENT_SCOPE)
    #set(${LIB_DEPS}     "Library dependencies" PARENT_SCOPE)

    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME TYPE)
    set(_MULTI_VALUE_ARGS HEADERS SOURCES DEPS)
    cmake_parse_arguments(LIB "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})


    #cmake_parse_arguments(
        #LIB_NAME    # Name of the library target
        #LIB_TYPE    # Type of the library to build
        #LIB_HEADERS # Library headers
        #LIB_SOURCES # Library sources
        #LIB_DEPS    # Library dependencies
        #LIB       # Prefix of the output variables, creates LIB_{NAME, TYPE, ...}
        #""        # List of names of boolean arguments
        #"NAME"    # Name of the library target
        #"TYPE"    # Type of the library to build

        #"NAME;TYPE"
        #"HEADERS;SOURCES;DEPS"

        #"HEADERS" # Library headers
        #"SOURCES" # Library sources
        #"DEPS"    # Library dependencies
        #${ARGN}     # arguments of the function to parse, here we take the all original ones
    #)

    message(STATUS "make_library arguments: ${LIB_NAME}, followed by ${ARGN}")
    message(STATUS "LIB_NAME: ${LIB_NAME}")
    message(STATUS "LIB_TYPE: ${LIB_TYPE}")
    message(STATUS "LIB_HEADERS: ${LIB_HEADERS}")
    message(STATUS "LIB_SOURCES: ${LIB_SOURCES}")
    message(STATUS "LIB_DEPS: ${LIB_DEPS}")

    #if(${LIB_TYPE} STREQUAL "static")
    if(${LIB_TYPE} STREQUAL "static")
        # Build a static library
        set(TARGET ${LIB_NAME}_static)
    else()
        # Build a shared library by default
        set(TARGET ${LIB_NAME})
    endif()
    add_library(${TARGET})

    # Set sources
    #set(${TARGET}
        #PRIVATE ${LIB_SOURCES}
        #PUBLIC  ${LIB_HEADERS})

    target_sources(${TARGET}
        PRIVATE ${LIB_SOURCES}
        PUBLIC  ${LIB_HEADERS})
    #target_sources(${TARGET} LIB_SOURCES)

    target_include_directories(${TARGET} PUBLIC ${LIB_HEADERS})
    target_link_libraries(${TARGET} PRIVATE ${LIB_DEPS})
    target_compile_features(${TARGET} PUBLIC cxx_std_20)

    source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${LIB_HEADERS})
#endfunction()
endfunction()


# ================ File Library ================
set(FILE_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(FILE_LIBRARY_SRCS File.cpp)
set(FILE_LIBRARY_DEPS fmt)

set(TARGET_SHARED files)
set(TARGET_STATIC files_static)

# Add both shared and static library targets
#make_library(files shared "${FILE_LIBRARY_HEADERS}" "${FILE_LIBRARY_SRCS}" "${FILE_LIBRARY_DEPS}")
make_library(
    NAME files
    TYPE shared
    HEADERS "${FILE_LIBRARY_HEADERS}"
    SOURCES "${FILE_LIBRARY_SRCS}"
    DEPS "${FILE_LIBRARY_DEPS}")

#make_library("files" "shared" "${FILE_LIBRARY_HEADERS}" "${FILE_LIBRARY_SRCS}" "${FILE_LIBRARY_DEPS}")
#make_library("files" "static" "${FILE_LIBRARY_HEADERS}" "${FILE_LIBRARY_SRCS}" "${FILE_LIBRARY_DEPS}")


#add_library(${TARGET_SHARED})
#add_library(${TARGET_STATIC})

## Set sources
#set(TARGET_SOURCES 
    #PRIVATE File.cpp
    #PUBLIC  ${FILE_LIBRARY_HEADERS})

#target_sources(${TARGET_SHARED} ${TARGET_SOURCES})
#target_sources(${TARGET_STATIC} ${TARGET_STATIC})

#target_include_directories(${TARGET_SHARED} PUBLIC ${FILE_LIBRARY_HEADERS})
#target_link_libraries(${TARGET} PRIVATE fmt)
#target_compile_features(${TARGET} PUBLIC cxx_std_20)

#source_group(
  #TREE "${PROJECT_SOURCE_DIR}/include"
  #PREFIX "Header Files"
  #FILES ${FILE_LIBRARY_HEADERS})

# ================ Image Library ================
set(IMAGE_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET image_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE Image.cpp 
    PUBLIC  ${IMAGE_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${IMAGE_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${IMAGE_LIBRARY_HEADERS})

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

