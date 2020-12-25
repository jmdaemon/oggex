set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/file" "${OGGEX_SOURCE_DIR}/include/base64")
set(TARGET audio_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE metadata.cpp 
    PRIVATE ExtractAudio.cpp
    PRIVATE Audio.cpp
    PRIVATE File.cpp
    PRIVATE base64.cpp
    PRIVATE EmbedAudio.cpp
    PUBLIC  ${HEADER_LIST}
)

target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
target_link_libraries(${TARGET} PRIVATE fmt image_library)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
