# Include QT header and ui files
set(QT_HEADERS ${PROJECT_SOURCE_DIR}/include/qt)
set(QT_UI ${PROJECT_SOURCE_DIR}/resources/qt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# QT6 libs must be available
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include all QT headers, ui files for all targets
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/qt ${PROJECT_SOURCE_DIR}/resources/qt)
set(QT6_DEPENDS Qt6::Widgets)

# Data Model
make_qt6(
    NAME datamodel
    SRCS datamodel.cpp
    HDRS ${HEADERS}
    DEPS ${QT6_DEPENDS}
    UI_HDRS ${QT_HEADERS}/datamodel.h)

# File Chooser
make_qt6(
    NAME filechooser
    SRCS filechooser.cpp
    HDRS ${HEADERS}
    DEPS ${QT6_DEPENDS}
    UI_HDRS ${QT_HEADERS}/filechooser.h
    UI_SRCS ${QT_UI}/filechooser.ui)

# Embed Widget
make_qt6(
    NAME embedwidget
    SRCS embedwidget.cpp
    HDRS ${HEADERS}
    DEPS ${QT6_DEPENDS} datamodel filechooser ${PKG_DEPENDS}
    UI_HDRS ${QT_HEADERS}/embedwidget.h
    UI_SRCS ${QT_UI}/embedwidget.ui)

# Extract Widget
make_qt6(
    NAME extractwidget
    SRCS extractwidget.cpp
    HDRS ${HEADERS}
    DEPS ${QT6_DEPENDS} datamodel filechooser ${PKG_DEPENDS}
    UI_HDRS ${QT_HEADERS}/extractwidget.h
    UI_SRCS ${QT_UI}/extractwidget.ui)

# Home Widget
make_qt6(
    NAME homewidget
    SRCS homewidget.cpp
    HDRS ${HEADERS}
    DEPS ${QT6_DEPENDS} filechooser embedwidget extractwidget ${PKG_DEPENDS}
    UI_HDRS ${QT_HEADERS}/homewidget.h
    UI_SRCS ${QT_UI}/homewidget.ui)

# Main Window
make_qt6(
    NAME mainwindow
    SRCS mainwindow.cpp
    HDRS ${HEADERS}
    DEPS ${QT6_DEPENDS} embedwidget extractwidget filechooser ${PKG_DEPENDS}
    UI_HDRS ${QT_HEADERS}/mainwindow.h
    UI_SRCS ${QT_UI}/mainwindow.ui)

set(QT_COMPONENTS datamodel filechooser embedwidget extractwidget mainwindow homewidget)

# QT6 Executable
set(TARGET oggex)
set(QT6_BIN_NAME ${TARGET}-qt)
qt_add_executable(${QT6_BIN_NAME} oggex-qt.cpp)
target_include_directories(${QT6_BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${QT6_BIN_NAME} PRIVATE ${QT6_DEPENDS} ${QT_COMPONENTS} ${PKG_DEPENDS} oggex cli ogx)
