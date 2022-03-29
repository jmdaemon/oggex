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
#set(UI_SOURCES ui/mainwindow.ui)
#set(UI_PATH "ui")
#set(EMBED_SOURCES embedwindow.h embedwindow.cpp "${UI_PATH}/embedwindow.ui")
#set(EMBED_SOURCES embedwindow.h embedwindow.cpp ui/embedwindow.ui)
set(EMBED_SOURCES embedwidget.h embedwidget.cpp embedwidget.ui)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        #"${UI_PATH}/mainwindow.ui"
        ui/mainwindow.ui
        ${EMBED_SOURCES}
)

qt_add_executable(oggex-qt ${PROJECT_SOURCES})
target_link_libraries(oggex-qt PRIVATE Qt6::Widgets)
