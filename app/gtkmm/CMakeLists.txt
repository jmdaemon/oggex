# Configure oggex-config.h
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(GETTEXT_PACKAGE ${PROJECT_NAME})
set(LOCALEDIR "/usr/share/locale/")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/oggex-config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/oggex-config.h")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

subdirs(src)
