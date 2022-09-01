# Encapsulates a string in quotes
function(quote var_name string)
    set(${var_name} "\"${string}\"" CACHE INTERNAL "")
endfunction()

# Configure oggex-config.h
set(PACKAGE_VERSION ${PROJECT_VERSION} CACHE INTERNAL "")
set(GETTEXT_PACKAGE ${PROJECT_NAME} CACHE INTERNAL "")
set(PROGRAM_NAME ${PROJECT_NAME} CACHE INTERNAL "")
set(LOCALEDIR "/usr/share/locale/" CACHE INTERNAL "")

set(APP_ID "io.github.com.jmdaemon.${PROGRAM_NAME}" CACHE INTERNAL "")
string(REPLACE "." "/" APP_ID_UI ${APP_ID})
string(PREPEND APP_ID_UI "/")
set(RESOURCES_DIR "../../../resources/gtk" CACHE INTERNAL "")

# UI Files
quote(UI_OGGEX_WINDOW "${APP_ID_UI}/${RESOURCES_DIR}/oggex-window.ui")
quote(UI_HELP_OVERLAY "${APP_ID_UI}/${RESOURCES_DIR}/help-overlay.ui")
quote(UI_FILE_CHOOSER_BUTTON "${APP_ID_UI}/${RESOURCES_DIR}/filechooserbutton.ui")
quote(UI_EMBED_WIDGET "${APP_ID_UI}/${RESOURCES_DIR}/embedwidget.ui")
quote(UI_EXTRACT_WIDGET "${APP_ID_UI}/${RESOURCES_DIR}/extractwidget.ui")

# Quote necessary variables for config file
quote(PACKAGE_VERSION ${PACKAGE_VERSION})
quote(GETTEXT_PACKAGE ${GETTEXT_PACKAGE})
quote(PROGRAM_NAME ${PROGRAM_NAME})
quote(LOCALEDIR ${LOCALEDIR})

quote(APP_ID ${APP_ID})
quote(APP_ID_UI ${APP_ID_UI})
quote(RESOURCES_DIR "../../../resources/gtk")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/oggex-config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/oggex-config.h")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

subdirs(src)
