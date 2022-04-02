set(HEADER_LIST "${OGGEX_SOURCE_DIR}/app/qt/embedwidget")
set(TARGET embedwidget)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE embedwidget.cpp
    PRIVATE embedwidget.ui
    PRIVATE datamodel.cpp
    PUBLIC  ${HEADER_LIST}
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${OGGEX_SOURCE_DIR}/app/qt"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
