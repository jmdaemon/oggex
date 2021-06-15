set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util" )

set(EXTRACT extract)
set(EMBED embed)

add_executable(${EXTRACT})
add_executable(${EMBED})

target_sources(${EXTRACT}
    PRIVATE extract.cpp
    PUBLIC  ${HEADER_LIST}
)

target_sources(${EMBED} 
    PRIVATE embed.cpp
    PUBLIC  ${HEADER_LIST}
)

target_include_directories(${EXTRACT} PUBLIC ${HEADER_LIST})
target_include_directories(${EMBED} PUBLIC ${HEADER_LIST})

target_link_libraries(${EXTRACT} PRIVATE fmt image_library audio audio_library file_library cmd_library)
target_link_libraries(${EMBED} PRIVATE fmt image_library audio audio_library file_library cmd_library)

target_compile_features(${EXTRACT} PUBLIC cxx_std_20)
target_compile_features(${EMBED} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
