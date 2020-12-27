set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/file" )
set(OGGEX oggex)

add_executable(${OGGEX})
target_sources(${OGGEX}
    PRIVATE oggex.cpp
    PUBLIC ${HEADER_LIST}
    )

#target_include_directories(${OGGEX} PUBLIC ${HEADER_LIST} ${GLIB_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
target_include_directories(${OGGEX} PUBLIC ${HEADER_LIST})

#target_link_libraries(${OGGEX} PRIVATE fmt ${GLIB2_LIBRARY_DIRS} ${GTK3_LIBRARY_DIRS} ${GTKMM_LIBRARY_DIRS} ${GTKMM_LIBRARIES}})
#target_link_libraries(${OGGEX} PRIVATE fmt ${GLIB_LDFLAGS} ${GTK3_LIBRARY_DIRS} ${GTKMM_LIBRARY_DIRS} ${GTKMM_LIBRARIES}})
target_link_libraries(${OGGEX} PRIVATE fmt  PkgConfig::GTKMM) 

target_compile_features(${OGGEX} PUBLIC cxx_std_20)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
