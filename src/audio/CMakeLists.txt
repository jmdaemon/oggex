make_static_shared_lib(
    NAME audio
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES EmbedAudio.cpp ExtractAudio.cpp
    DEPS fmt utility image audio_library
    SRC_GROUP_FILES ${AUDIO_DIR})
