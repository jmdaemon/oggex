set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/file" "${OGGEX_SOURCE_DIR}/include/ui" "${OGGEX_SOURCE_DIR}/include/ui/view")
set(OGGEX oggex)

# GResources
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)
set(GRESOURCE_C             oggex.gresource.c)
set(GRESOURCE_XML           oggex.gresource.xml)
set(GRESOURCE_XML_IN        oggex.gresource.xml.in)
set(GRESOURCE_DEPENDENCIES  CACHE INTERNAL "GResource dependencies for Dashboard UI")

set(OLD ${CMAKE_CURRENT_SOURCE_DIR}/${GRESOURCE_XML_IN})
set(NEW ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_XML})

if(NOT EXISTS ${NEW} OR (${OLD} IS_NEWER_THAN ${NEW}))
    configure_file(${GRESOURCE_XML_IN} ${GRESOURCE_XML})

    execute_process(
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${GLIB_COMPILE_RESOURCES} --generate-dependencies ${GRESOURCE_XML}
        OUTPUT_VARIABLE GRESOURCE_DEPENDENCIES
    )

    string(REPLACE "\n" ";" GRESOURCE_DEPENDENCIES ${GRESOURCE_DEPENDENCIES})
    list(POP_BACK GRESOURCE_DEPENDENCIES)
endif()

add_custom_command(
    OUTPUT ${GRESOURCE_C}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/xml/gtk3/
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
        --generate-source ${NEW}
    VERBATIM
    MAIN_DEPENDENCY ${GRESOURCE_XML}
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/resources/xml/gtk3/${GRESOURCE_DEPENDENCIES}"
)

set(GRESOURCE_FILES dashboard-resource) 

add_custom_target(
    ${GRESOURCE_FILES}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
) # End of GResource
set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
    PROPERTIES GENERATED TRUE
)

add_executable(${OGGEX})
add_dependencies(${OGGEX} ${GRESOURCE_FILES})

set(VIEW_DIR view)
set(CONTROL_DIR controller)

set (GTK3_SOURCES
    PRIVATE ${CONTROL_DIR}/DashboardWindow.cpp
    PRIVATE ${CONTROL_DIR}/Dashboard.cpp
    #PRIVATE ${CONTROL_DIR}/FileSelect.cpp
    #PRIVATE ${CONTROL_DIR}/FileSelectWindow.cpp
    PRIVATE ${CONTROL_DIR}/Embed.cpp
    PRIVATE ${CONTROL_DIR}/EmbedWindow.cpp
    PRIVATE ${VIEW_DIR}/SoundTagManager.cpp
    PRIVATE ${VIEW_DIR}/AudioInputManager.cpp
    )

target_sources(${OGGEX}
    PRIVATE oggex.cpp
    ${GTK3_SOURCES}
    PUBLIC ${HEADER_LIST}
    )

target_include_directories(${OGGEX} PUBLIC ${HEADER_LIST} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${OGGEX} PRIVATE fmt PkgConfig::GTKMM) 

set_target_properties(${OGGEX} PROPERTIES
    RESOURCE "${GLADE_FILES}" RESOURCE ${GRESOURCE_FILES})

target_compile_features(${OGGEX} PUBLIC cxx_std_20)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
