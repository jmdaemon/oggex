set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio")
set(TARGET audio_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE metadata.cpp 
    PRIVATE EmbedAudio.cpp
    PUBLIC  ${HEADER_LIST}
)

target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
