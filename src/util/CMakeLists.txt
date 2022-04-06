# Build targets with library options
set(DEFAULT_CXX_FLAGS -Werror -Wall -Wextra -pedantic)
set(LIB_CXX_FLAGS -fPIC -g)
set(REL_CXX_FLAGS -O3 -DNDEBUG)

function(lslib)
    # Set make_library arguments
    set(ARG_PREFIX LIB)
    set(_OPTIONS_ARGS )
    set(_ONE_VALUE_ARGS NAME)
    set(_MULTI_VALUE_ARGS HEADERS)

    cmake_parse_arguments(${ARG_PREFIX} "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    message(STATUS, "Library Target Name: ${LIB_NAME}")
    message(STATUS, "Library Headers Directory: ${LIB_HEADERS}")
endfunction()

lslib(
    NAME ${UTILITY_LIB}
    HEADERS ${UTILITY_HEADERS})

#message(STATUS, "UTILITY_HEADERS: ${UTILITY_HEADERS}")
#message(STATUS, "UTILITY_LIB: ${UTILITY_LIB}")

# ================ File Library ================
# Add both shared and static library targets
make_static_shared_lib(NAME file
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_HEADERS} ${UTILITY_DIR}
    SOURCES File.cpp
    DEPS fmt ${UTILITY_LIB}
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(file PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS} -I${UTILITY_HEADERS})

# ================ Image Library ================
make_static_shared_lib(
    NAME image
    CSTANDARD cxx_std_11
    HEADERS ${UTILITY_DIR}
    SOURCES Image.cpp
    DEPS fmt
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(image PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})

# ================ Audio Library ================
make_static_shared_lib(
    NAME audio_library
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Audio.cpp Mask.cpp
    DEPS fmt file image
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(audio_library PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})
# ================ Command Library ================
make_static_shared_lib(
    NAME cmd
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Data.cpp Cmd.cpp InputParser.cpp
    DEPS fmt
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(cmd PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})
