#make_static_shared_lib(
    #NAME audio
    #CSTANDARD ${CSTANDARD}
    ##HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    #HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    #SOURCES EmbedAudio.cpp ExtractAudio.cpp
    ##DEPS fmt image audio_library)
    #DEPS fmt utility image audio_library
    #SRC_GROUP_FILES ${AUDIO_DIR}
    #)

# ================ Audio Library ================
set(LIBRARY_HEADERS ${AUDIO_DIR} ${UTILITY_DIR} ${UTILITY_HEADERS})

set(LIBRARY_HEADERS ${AUDIO_DIR} ${UTILITY_DIR})
set(TARGET audio)

add_library(${TARGET} SHARED)
target_sources(${TARGET}
    PRIVATE EmbedAudio.cpp ExtractAudio.cpp
    PUBLIC  ${LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt utility)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
    TREE "${INCLUDES_DIR}"
    PREFIX "Header Files"
    FILES ${AUDIO_DIR})
