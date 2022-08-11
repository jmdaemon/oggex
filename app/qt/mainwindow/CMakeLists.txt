#set(QT_HEADERS
    #"${PROJECT_SOURCE_DIR}/app/qt/embedwidget"
    #"${PROJECT_SOURCE_DIR}/app/qt/mainwindow")
set(TARGET mainwindow)

qt6_wrap_cpp(HEADER ${QT_HEADERS}/mainwindow.h)
#qt6_wrap_ui(mainwindow.ui mainwindow.ui)
#qt6_wrap_ui(UI mainwindow.ui)

add_library(${TARGET} mainwindow.cpp mainwindow.ui ${HEADER})
#target_sources(${TARGET}
    #PRIVATE mainwindow.cpp
    #PRIVATE mainwindow.ui
    #PUBLIC  ${QT_HEADERS})

#find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_include_directories(${TARGET} PUBLIC ${QT_HEADERS})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget)
#target_compile_features(${TARGET} PUBLIC cxx_std_20)

#source_group (
  #TREE "${PROJECT_SOURCE_DIR}/app/qt"
  #PREFIX "Header Files"
  #FILES ${QT_HEADERS})
