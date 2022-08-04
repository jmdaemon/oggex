#make_static_shared_lib(
    #NAME oggex
    #CSTANDARD ${CSTANDARD}
    #HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    #SOURCES EmbedAudio.cpp ExtractAudio.cpp
    #DEPS fmt utility image audio
    #SRC_GROUP_FILES ${AUDIO_DIR})
make_ssl(
    NAME oggex
    HDRS ${INCLUDES_DIR}/oggex ${INCLUDES_DIR}/utility
    SRCS EmbedAudio.cpp ExtractAudio.cpp
    DEPS fmt utility image audio)
