set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Compile the needed individual components
# EmbedWidget
add_subdirectory("embedwidget")
add_subdirectory("mainwindow")
#set(EMBED_WIDGET_DIR "embedwidget")
#set(EMBED_WIDGET_SOURCES ${EMBED_WIDGET_DIR}/embedwidget.cpp,
    #${EMBED_WIDGET_DIR}/embedwidget.h ${EMBED_WIDGET_DIR}/embedwidget.ui)

# MainWindow
#set(MAIN_WINDOW_DIR "mainwindow")
#set(MAIN_SOURCES ${MAIN_WINDOW_DIR}/mainwindow.cpp
    #${MAIN_WINDOW_DIR}/mainwindow.h ${MAIN_WINDOW_DIR}/mainwindow.ui)

#set(PROJECT_SOURCES
        #main.cpp
        #${MAIN_SOURCES}
#)

set(QTUI_HEADERS_DIR "${OGGEX_SOURCE_DIR}/app/qt")
set(HEADER_LIST "${QTUI_HEADERS_DIR}/embedwidget" "${QTUI_HEADERS_DIR}/mainwindow")
set(TARGET oggex-qt)

# Include necessary header files
#target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
#target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwiget mainwindow)

qt_add_executable(${TARGET} main.cpp)
target_include_directories(${TARGET} PUBLIC ${HEADER_LIST})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget mainwindow)

#set(PROJECT_SOURCES main.cpp
        ##${MAIN_SOURCES}
#)

#qt_add_executable(oggex-qt ${PROJECT_SOURCES})
#target_link_libraries(oggex-qt PRIVATE Qt6::Widgets embedwidget)
#target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget)
