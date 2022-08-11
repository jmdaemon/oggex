# Include QT header files
set(QT_HEADERS ${PROJECT_SOURCE_DIR}/include/qt)

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

include_directories(${QT_HEADERS})

# Compile the needed individual components
add_subdirectory("datamodel")
add_subdirectory("embedwidget")
add_subdirectory("mainwindow")


# Build the main executable
set(TARGET oggex-qt)
qt_add_executable(${TARGET} main.cpp)

#qt6_wrap_cpp(mainwindow/mainwindow.cpp ${QT_HEADERS}/mainwindow.h)
#qt6_wrap_ui(mainwindow/mainwindow.ui mainwindow/mainwindow.ui)

#qt6_wrap_cpp(embedwidget/embedwidget.cpp ${QT_HEADERS}/embedwidget.h)
#qt6_wrap_ui(embedwidget/embedwidget.ui embedwidget/embedwidget.ui)

# Include necessary header files & link components
#target_include_directories(${TARGET} PUBLIC ${QT_HEADERS} ./mainwindow ./embedwidget ./datamodel)
target_include_directories(${TARGET} PUBLIC ${QT_HEADERS})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget mainwindow)
