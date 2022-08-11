#set(QT_HEADERS
    #"${PROJECT_SOURCE_DIR}/app/qt/embedwidget"
    #"${PROJECT_SOURCE_DIR}/app/qt/datamodel")
set(TARGET embedwidget)

qt6_wrap_cpp(HEADER ${QT_HEADERS}/embedwidget.h)
#qt6_wrap_ui(embedwidget.ui embedwidget.ui)
#qt5_wrap_ui(embedwidget.ui /MainWindow.ui)

add_library(${TARGET} embedwidget.cpp embedwidget.ui ${HEADER})
#target_sources(${TARGET}
    #PRIVATE embedwidget.cpp
    #PRIVATE embedwidget.ui
    #PUBLIC  ${QT_HEADERS})

#find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_include_directories(${TARGET} PUBLIC ${QT_HEADERS})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets datamodel)
#target_compile_features(${TARGET} PUBLIC cxx_std_20)

#source_group(
  #TREE "${PROJECT_SOURCE_DIR}/app/qt"
  #PREFIX "Header Files"
  #FILES ${QT_HEADERS})
