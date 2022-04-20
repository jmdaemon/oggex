# Build targets with library options
set(DEFAULT_CXX_FLAGS -Wall -Wextra -pedantic)
set(REL_CXX_FLAGS -O3 -DNDEBUG)
set(DBG_CXX_FLAGS -g -O0 -DDEBUG)
set(LIB_CXX_FLAGS -fPIC -g)

# ================ File Library ================
# Add both shared and static library targets
make_static_shared_lib(
    NAME file
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR}
    SOURCES File.cpp
    DEPS fmt utility
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(file PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})

# ================ Image Library ================
make_static_shared_lib(
    NAME image
    CSTANDARD cxx_std_11
    HEADERS ${UTILITY_DIR}
    SOURCES Image.cpp
    DEPS fmt utility
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(image PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})

# ================ Audio Library ================
make_static_shared_lib(
    NAME audio
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Audio.cpp Mask.cpp
    DEPS fmt utility file image
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(audio PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})

# ================ Command Library ================
make_static_shared_lib(
    NAME cmd
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Data.cpp Cmd.cpp
    DEPS fmt cnc
    SRC_GROUP_FILES ${UTILITY_DIR})

target_compile_options(cmd PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})
