make_static_shared_lib(
    NAME oggex
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES EmbedAudio.cpp ExtractAudio.cpp
    DEPS fmt utility image audio
    SRC_GROUP_FILES ${AUDIO_DIR})
