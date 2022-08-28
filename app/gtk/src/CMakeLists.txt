
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk)
set(GTK4_DEPENDS)
set(TARGET oggex)

# Find GTK sources
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)

set(GTK4_BIN_NAME ${TARGET}-gtk)
add_executable(${GTK4_BIN_NAME} main.c oggex-window.c oggex-application.c)
target_include_directories(${GTK4_BIN_NAME} PUBLIC ${HEADERS} ${GTK4_LIBRARY_DIRS})
target_link_libraries(${GTK4_BIN_NAME} PRIVATE ${GTK4_DEPENDS} ${GTK4_LIBRARIES})
