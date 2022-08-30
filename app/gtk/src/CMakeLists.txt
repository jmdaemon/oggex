set(TARGET oggex)

# Include gtk4 cmake module
include(gtk4)

# Add the rest of the GTK sources
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk ${GTK4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
set(GTK4_DEPENDS ${GTK4_LIBRARIES})

# GResources
set(GR_C oggex-resources.c)
set(GR_H oggex-resources.h)
set(GR_XML oggex.gresource.xml)
set(GR_C_OUT ${CMAKE_CURRENT_BINARY_DIR}/${GR_C}) 
set(GR_H_OUT ${CMAKE_CURRENT_BINARY_DIR}/${GR_H}) 
set(GR ${TARGET}-resources)

make_gresource(
    NAME ${GR}
    SRC ${GR_C}
    SRC_OUT ${GR_C_OUT}
    HDR ${GR_H}
    HDR_OUT ${GR_H_OUT}
    WD ${CMAKE_CURRENT_SOURCE_DIR}
    XML ${GR_XML})

# Build oggex-gtk
set(GTK4_BIN_NAME ${TARGET}-gtk)
add_executable(${GTK4_BIN_NAME} ${GR_C_OUT} oggex_defs.c embedwidget.c extractwidget.c oggex-window.c oggex-application.c main.c)
target_include_directories(${GTK4_BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${GTK4_BIN_NAME} PRIVATE ${GTK4_DEPENDS})

# Specify generated resource files
add_dependencies(${GTK4_BIN_NAME} ${GR})
