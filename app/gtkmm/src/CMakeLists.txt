set(TARGET oggex)

# Include gtk4 cmake module
include(gtkmm4)

# Add the rest of the GTK sources
#set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk ${GTK4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
#set(GTK4_DEPENDS ${GTK4_LIBRARIES})
set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${PROJECT_SOURCE_DIR}/include/gtk ${PROJECT_SOURCE_DIR}/resources/gtk ${GTKMM4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
set(GTKMM4_DEPENDS ${GTKMM4_LIBRARIES})


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
set(GTKMM4_BIN_NAME ${TARGET}-gtk)
#add_executable(${GTKMM4_BIN_NAME} ${GR_C_OUT} oggex_defs.c oggex-window.c oggex-application.c main.c)
#add_executable(${GTKMM4_BIN_NAME} ${GR_C_OUT} oggex_defs.c oggexappwindow.cpp oggexapp.cpp oggex-gtk.cpp)
add_executable(${GTKMM4_BIN_NAME} ${GR_C_OUT} oggex_defs.c appwindow.cpp app.cpp oggex-gtk.cpp)
target_include_directories(${GTKMM4_BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${GTKMM4_BIN_NAME} PRIVATE ${GTKMM4_DEPENDS})

# Specify generated resource files
add_dependencies(${GTKMM4_BIN_NAME} ${GR})
