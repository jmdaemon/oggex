set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/image")

add_library(image_library)
target_sources(image_library
    PRIVATE image.cpp 
    PUBLIC  ${HEADER_LIST}
)

target_include_directories(image_library PUBLIC ${OGGEX_SOURCE_DIR}/include/image)
target_link_libraries(image_library PRIVATE ${OpenCV_LIBS})
target_compile_features(image_library PUBLIC cxx_std_11)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
