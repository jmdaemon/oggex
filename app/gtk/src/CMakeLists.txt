set(TARGET oggex)

# Find GTK sources
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

# Add the rest of the GTK sources
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk ${GTK4_INCLUDE_DIRS})
set(GTK4_DEPENDS ${GTK4_LIBRARIES})

add_definitions(${GTK4_CFLAGS_OTHER})
link_directories(${GTK4_LIBRARY_DIRS})

# Compile program gresource files
set(RESOURCE_DIR ${PROJECT_SOURCE_DIR}/resources/gtk)
set(GRESOURCE_C oggex-resources.c)
set(GRESOURCE_H oggex-resources.h)
set(GRESOURCE_XML oggex.gresource.xml)
set(GRESOURCE_OUT ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}) 
set(GRESOURCE_HEADER ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_H}) 
set(GRESOURCES ${TARGET}-resources)

# Generate the gresource source file
add_custom_command(
    OUTPUT ${GRESOURCE_C}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${GRESOURCE_OUT} --generate-source --internal
        ${GRESOURCE_XML}
    VERBATIM
    MAIN_DEPENDENCY ${GRESOURCE_XML}
    DEPENDS
        ${RESOURCE_DIR}/help-overlay.ui
        ${RESOURCE_DIR}/oggex-window.ui)

# Generate the gresource header file
add_custom_command(
    OUTPUT ${GRESOURCE_H}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${GRESOURCE_HEADER} --generate-header --internal
        ${GRESOURCE_XML}
    VERBATIM
    MAIN_DEPENDENCY ${GRESOURCE_XML})

add_custom_target(${GRESOURCES} DEPENDS ${GRESOURCE_OUT} ${GRESOURCE_HEADER})

# Build oggex-gtk
set(GTK4_BIN_NAME ${TARGET}-gtk)
add_executable(${GTK4_BIN_NAME} ${GRESOURCE_OUT} oggex_defs.c oggex-window.c oggex-application.c main.c)
#add_executable(${GTK4_BIN_NAME} oggex_defs.c oggex-window.c oggex-application.c main.c)
target_include_directories(${GTK4_BIN_NAME} PUBLIC ${HEADERS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${GTK4_BIN_NAME} PRIVATE ${GTK4_DEPENDS})
# Specify generated resource files
set_source_files_properties(${GRESOURCE_OUT} ${GRESOURCE_HEADER} PROPERTIES GENERATED TRUE)
#set_source_files_properties(${GRESOURCE_HEADER} PROPERTIES GENERATED TRUE)
add_dependencies(${GTK4_BIN_NAME} ${GRESOURCES})
