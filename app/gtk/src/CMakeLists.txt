set(TARGET oggex)

# Find GTK sources
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

# Add the rest of the GTK sources
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk ${GTK4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
set(GTK4_DEPENDS ${GTK4_LIBRARIES})

add_definitions(${GTK4_CFLAGS_OTHER})
link_directories(${GTK4_LIBRARY_DIRS})


set(GRESOURCE_C oggex-resources.c)
set(GRESOURCE_H oggex-resources.h)
set(GRESOURCE_XML oggex.gresource.xml)
set(GRESOURCE_OUT ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}) 
set(GRESOURCE_HEADER ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_H}) 
set(GRESOURCES ${TARGET}-resources)

make_gresource(
    NAME ${GRESOURCES}
    SRC ${GRESOURCE_C}
    SRC_OUT ${GRESOURCE_OUT}
    HDR ${GRESOURCE_H}
    HDR_OUT ${GRESOURCE_HEADER}
    WD ${CMAKE_CURRENT_SOURCE_DIR}
    XML ${GRESOURCE_XML})

# Build oggex-gtk
set(GTK4_BIN_NAME ${TARGET}-gtk)
add_executable(${GTK4_BIN_NAME} ${GRESOURCE_OUT} oggex_defs.c oggex-window.c oggex-application.c main.c)
target_include_directories(${GTK4_BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${GTK4_BIN_NAME} PRIVATE ${GTK4_DEPENDS})

# Specify generated resource files
set_source_files_properties(${GRESOURCE_OUT} ${GRESOURCE_HEADER} PROPERTIES GENERATED TRUE)
add_dependencies(${GTK4_BIN_NAME} ${GRESOURCES})
