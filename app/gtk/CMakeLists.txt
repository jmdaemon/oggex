# Configure oggex-config.h
set(PACKAGE_VERSION ${PROJECT_VERSION})
set(GETTEXT_PACKAGE ${PROJECT_NAME})
set(PROGRAM_NAME ${PROJECT_NAME})
set(LOCALEDIR "/usr/share/locale/")

set(APP_ID "/io/github/com/jmdaemon/oggex")
set(RESOURCES_DIR "../../../resources/gtk")

# UI Files
set(UI_OGGEX_WINDOW "${APP_ID}/${RESOURCES_DIR}/oggex-window.ui")
set(UI_HELP_OVERLAY "${APP_ID}/${RESOURCES_DIR}/help-overlay.ui")
set(UI_FILE_CHOOSER_BUTTON "${APP_ID}/${RESOURCES_DIR}/filechooserbutton.ui")
set(UI_EMBED_WIDGET "${APP_ID}/${RESOURCES_DIR}/embedwidget.ui")
set(UI_EXTRACT_WIDGET "${APP_ID}/${RESOURCES_DIR}/extractwidget.ui")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/oggex-config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/oggex-config.h")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

subdirs(src)
