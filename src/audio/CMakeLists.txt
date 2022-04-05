make_static_shared_lib(
    NAME audio
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES EmbedAudio.cpp ExtractAudio.cpp
    DEPS fmt image audio_library)
