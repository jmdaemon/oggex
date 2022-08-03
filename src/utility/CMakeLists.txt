# File
make_static_shared_lib( # Add both shared and static library targets
    NAME file
    SOURCES File.cpp
    HEADERS ${UTILITY_DIR}
    DEPS fmt utility
    CSTANDARD ${CSTANDARD}
    SRC_GROUP_FILES ${UTILITY_DIR})

# Image
make_static_shared_lib(
    NAME image
    SOURCES Image.cpp
    HEADERS ${UTILITY_DIR}
    DEPS fmt utility
    CSTANDARD cxx_std_11
    SRC_GROUP_FILES ${UTILITY_DIR})

# Audio
make_static_shared_lib(
    NAME audio
    SOURCES Audio.cpp Mask.cpp
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    DEPS fmt utility file image
    CSTANDARD ${CSTANDARD}
    SRC_GROUP_FILES ${UTILITY_DIR})

# Command
make_static_shared_lib(
    NAME cmd
    SOURCES Data.cpp Cmd.cpp
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    DEPS fmt cnc bytesize
    CSTANDARD ${CSTANDARD}
    SRC_GROUP_FILES ${UTILITY_DIR})
