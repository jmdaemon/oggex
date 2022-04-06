# Build targets with library options
set(DEFAULT_CXX_FLAGS -Werror -Wall -Wextra -pedantic)
set(LIB_CXX_FLAGS -fPIC -g)
set(REL_CXX_FLAGS -O3 -DNDEBUG)
# ================ File Library ================
# Add both shared and static library targets
#make_static_shared_lib(
    #NAME file
    #CSTANDARD ${CSTANDARD}
    #HEADERS "${UTILITY_HEADERS} ${UTILITY_DIR}"
    ##HEADERS ${UTILITY_DIR}
    #SOURCES File.cpp
    ##DEPS fmt utility)
    #DEPS fmt ${UTILITY_LIB})
set(TARGET file)
set(LIB_HEADERS ${UTILITY_HEADERS} ${UTILITY_DIR})
set(LIB_SOURCES File.cpp)
set(LIB_DEPS fmt ${UTILITY_LIB})
set(LIB_CSTANDARD ${CSTANDARD})

add_library(${TARGET} SHARED)
target_sources(${TARGET}
    PRIVATE ${LIB_SOURCES}
    PUBLIC  ${LIB_HEADERS})

target_include_directories(${TARGET} PUBLIC ${LIB_HEADERS})
target_link_libraries(${TARGET} PRIVATE ${LIB_DEPS})
target_compile_features(${TARGET} PUBLIC ${LIB_CSTANDARD})

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${UTILITY_DIR})

message(STATUS, "UTILITY_HEADERS: ${UTILITY_HEADERS}")
message(STATUS, "UTILITY_LIB: ${UTILITY_LIB}")

target_compile_options(file PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})

# ================ Image Library ================
make_static_shared_lib(
    NAME image
    CSTANDARD cxx_std_11
    HEADERS ${UTILITY_DIR}
    SOURCES Image.cpp
    DEPS fmt)

target_compile_options(image PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})

# ================ Audio Library ================
make_static_shared_lib(
    NAME audio_library
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Audio.cpp Mask.cpp
    DEPS fmt file image)

target_compile_options(audio_library PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})
# ================ Command Library ================
make_static_shared_lib(
    NAME cmd
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Data.cpp Cmd.cpp InputParser.cpp
    DEPS fmt)

target_compile_options(cmd PRIVATE ${DEFAULT_CXX_FLAGS} ${REL_CXX_FLAGS} ${LIB_CXX_FLAGS})
