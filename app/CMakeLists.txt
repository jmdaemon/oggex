#set(HEADER_LIST "${OGGEX_SOURCE_DIR}/include/audio" "${OGGEX_SOURCE_DIR}/include/util" )

set(OGGEX oggex)
add_executable(${OGGEX})
target_sources(${OGGEX}
    PRIVATE oggex.cpp
    PUBLIC  ${HEADER_LIST}
)
target_include_directories(${OGGEX} PUBLIC ${AUDIO_DIR} ${UTILITY_DIR})
target_link_libraries(${OGGEX} PRIVATE fmt image sound audio file cmd)
target_compile_features(${OGGEX} PUBLIC cxx_std_20)
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
  )

install(TARGETS ${OGGEX} RUNTIME DESTINATION bin)
install(TARGETS ${OGGEX}
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)
install(TARGETS ${OGGEX}
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)
#add_subdirectory(qt)
