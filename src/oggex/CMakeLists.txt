set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/file" "${OGGEX_SOURCE_DIR}/include/ui")
#set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/file")
set(OGGEX oggex)

add_executable(${OGGEX})
target_sources(${OGGEX}
    PRIVATE oggex.cpp
    PRIVATE controller/DashboardController.cpp
    PRIVATE controller/DashboardWindow.cpp
    PUBLIC ${HEADER_LIST}
    )

target_include_directories(${OGGEX} PUBLIC ${HEADER_LIST})
target_link_libraries(${OGGEX} PRIVATE fmt  PkgConfig::GTKMM) 

FILE(COPY "../../resources/xml/Dashboard.glade" DESTINATION "${CMAKE_BINARY_DIR}")
set_target_properties(${OGGEX} PROPERTIES
    RESOURCE "${GLADE_FILES}" )

target_compile_features(${OGGEX} PUBLIC cxx_std_20)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
