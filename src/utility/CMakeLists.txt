set(HEADERS ${INCLUDES_DIR} ${UTILITY_DIR} ${AUDIO_DIR})

# Add both shared and static library targets
make_ssl(NAME file
    SRCS File.cpp
    HDRS ${HEADERS}
    HDR ${UTILITY_DIR}/File.h
    DEPS fmt utility bytesize)

make_ssl(NAME image
    SRCS Image.cpp
    HDRS ${HEADERS}
    HDR ${UTILITY_DIR}/Image.h
    DEPS fmt utility)

make_ssl(NAME audio
    SRCS Audio.cpp Mask.cpp
    HDRS ${HEADERS}
    HDR ${UTILITY_DIR}/Audio.h
    DEPS fmt utility file image)

make_ssl(NAME cmd
    SRCS Data.cpp Cmd.cpp
    HDRS ${HEADERS}
    HDR ${UTILITY_DIR}/Cmd.h
    DEPS fmt cnc bytesize)
