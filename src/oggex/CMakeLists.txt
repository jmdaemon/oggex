make_ssl(
    NAME oggex
    HDRS ${INCLUDES_DIR}/oggex ${INCLUDES_DIR}/utility
    #SRCS EmbedAudio.cpp ExtractAudio.cpp
    SRCS Oggex.cpp
    DEPS fmt utility image audio)
