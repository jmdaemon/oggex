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

# QT6 libs must be available
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include QT header directory to all targets
include_directories(${QT_HEADERS})

# Compile user interface components
# *Note* that we must use qt6_wrap_cpp, since AUTOMOC doesn't detect
# header files outside the current directory

## Data Model
set(TARGET datamodel)
qt6_wrap_cpp(HEADER ${QT_HEADERS}/datamodel.h)
add_library(${TARGET} datamodel.cpp ${HEADER})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets)

## Embed Widget
set(TARGET embedwidget)
qt6_wrap_cpp(HEADER ${QT_HEADERS}/embedwidget.h)
add_library(${TARGET} embedwidget.cpp embedwidget.ui ${HEADER})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets datamodel)

## Main Window
set(TARGET mainwindow)
qt6_wrap_cpp(HEADER ${QT_HEADERS}/mainwindow.h)
add_library(${TARGET} mainwindow.cpp mainwindow.ui ${HEADER})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget)

## Binary
set(TARGET oggex-qt)
qt_add_executable(${TARGET} oggex-qt.cpp)

# Include necessary header files & link components
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets embedwidget mainwindow)
