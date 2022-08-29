set(TARGET oggex)

# Find GTK sources
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
#pkg_check_modules(GLIB2 REQUIRED glib-2.0)

# Add the rest of the GTK sources
#set(GTK4_DEPENDS ${GTK4_DEPENDS} ${GTK4_LIBRARIES})
set(GTK4_DEPENDS ${GTK4_LIBRARIES})
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION}
    ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk
    #${GTK4_LIBRARY_DIRS} ${GLIB2_LIBRARY_DIRS})
    #${GTK4_INCLUDE_DIRS} ${GTK4_LIBRARY_DIRS})
    ${GTK4_INCLUDE_DIRS})

# Build oggex-gtk
#include_directories(${GTK4_INCLUDE_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})
#message(STATUS "GTK4_DEPENDS: ${GTK4_DEPENDS}")
link_directories(${GTK4_LIBRARY_DIRS})

set(GTK_PROJECT_CONFIG ${TARGET}-config)
add_custom_target(${GTK_PROJECT_CONFIG} DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/oggex-config.h)

set(GTK4_BIN_NAME ${TARGET}-gtk)
add_executable(${GTK4_BIN_NAME} oggex_defs.c oggex-window.c oggex-application.c main.c )
#target_link_directories(${GTK4_BIN_NAME} PUBLIC ${GTK4_LIBRARY_DIRS})
target_include_directories(${GTK4_BIN_NAME} PUBLIC ${HEADERS})
#target_link_libraries(${GTK4_BIN_NAME} PRIVATE ${LIBRARIES})
target_link_libraries(${GTK4_BIN_NAME} PRIVATE ${GTK4_DEPENDS})

