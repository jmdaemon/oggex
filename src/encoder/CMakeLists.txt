set(HEADER_LIST "${PROJECT_BINARY_DIR}")
set(TARGET encoder)

add_executable(${TARGET} ogg-encoder.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_11)
target_include_directories(${TARGET} PUBLIC libogg ${HEADER_LIST})
#target_link_libraries(${TARGET} PRIVATE image_library ogg libtag)
target_link_libraries(${TARGET} PRIVATE image_library ogg tag)
