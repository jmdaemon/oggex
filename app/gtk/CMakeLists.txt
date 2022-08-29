set(PACKAGE_VERSION ${PROJECT_VERSION})
set(GETTEXT_PACKAGE ${PROJECT_NAME})
set(LOCALEDIR "/usr/share/locale/")
# Configure gettext translations
#configure_file(

    #)

#add_custom_command(
    #OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/oggex-config.h
    #COMMAND echo "\n#pragma once\n\n#define GETTEXT_PACKAGE \"${GETTEXT_PACKAGE}\"\n\n#define LOCALEDIR \"${LOCALEDIR}\"\n\n#define PACKAGE_VERSION \"${PACKAGE_VERSION}\"")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/oggex-config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/oggex-config.h")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

subdirs(src)
