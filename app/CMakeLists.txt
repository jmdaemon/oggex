set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util" )

set(OGGEX oggex)
add_executable(${OGGEX})
target_sources(${OGGEX}
    PRIVATE oggex.cpp
    PUBLIC  ${HEADER_LIST}
)
target_include_directories(${OGGEX} PUBLIC ${HEADER_LIST})
target_link_libraries(${OGGEX} PRIVATE fmt image_library audio audio_library file_library cmd_library)
target_compile_features(${OGGEX} PUBLIC cxx_std_20)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
  )

#install(TARGETS ${OGGEX} DESTINATION install)
#set_target_properties(${OGGEX}
    #PROPERTIES
    #RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    #)
install(TARGETS ${OGGEX} RUNTIME DESTINATION bin)
install(TARGETS ${OGGEX}
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)
install(TARGETS ${OGGEX}
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)
add_subdirectory(qt)
