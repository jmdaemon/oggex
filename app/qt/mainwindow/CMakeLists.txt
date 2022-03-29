set(HEADER_LIST
    #"${OGGEX_SOURCE_DIR}/app/ui/mainwindow/mainwindow.h"
    #"${OGGEX_SOURCE_DIR}/app/ui/embedwidget/embedwidget.h")
    "${OGGEX_SOURCE_DIR}/app/qt/embedwidget"
    "${OGGEX_SOURCE_DIR}/app/qt/mainwindow"
    )
set(TARGET mainwindow)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE mainwindow.cpp
    PRIVATE mainwindow.ui
    PUBLIC  ${HEADER_LIST}
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group (
  #TREE "${PROJECT_SOURCE_DIR}/include"
  #TREE "${HEADER_LIST}"
  #TREE "${PROJECT_SOURCE_DIR}/app/qt/mainwindow"
  #TREE "${PROJECT_SOURCE_DIR}/app/qt/mainwindow"
  TREE "${OGGEX_SOURCE_DIR}/app/qt"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
