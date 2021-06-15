# ================ File Library ================
set(FILE_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET file_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE File.cpp
    PUBLIC  ${FILE_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${FILE_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${FILE_LIBRARY_HEADERS})

# ================ Image Library ================
set(IMAGE_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET image_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE Image.cpp 
    PUBLIC  ${IMAGE_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${IMAGE_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE)
target_compile_features(${TARGET} PUBLIC cxx_std_11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${IMAGE_LIBRARY_HEADERS})

# ================ Audio Library ================
set(AUDIO_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET audio_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE Audio.cpp
    PRIVATE Mask.cpp
    PUBLIC  ${AUDIO_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${AUDIO_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt image_library)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${AUDIO_LIBRARY_HEADERS})

# ================ Command Library ================
set(CMD_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET cmd_library)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE Cmd.cpp
    PRIVATE InputParser.cpp
    PUBLIC  ${CMD_LIBRARY_HEADERS}
)

target_include_directories(${TARGET} PUBLIC ${CMD_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${CMD_LIBRARY_HEADERS})

