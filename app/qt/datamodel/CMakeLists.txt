set(HEADER_LIST "${PROJECT_SOURCE_DIR}/app/qt/datamodel")
set(TARGET datamodel)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE datamodel.cpp
    PUBLIC  ${HEADER_LIST}
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/app/qt"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
