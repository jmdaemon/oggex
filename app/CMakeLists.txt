set(HEADERS ${INCLUDES_DIR} ${INCLUDES_DIR}/utility)
set(TARGET oggex)

set(BIN_NAME oggex-bin)
add_executable(${BIN_NAME} oggex-bin.cpp)
target_include_directories(${BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${BIN_NAME} PRIVATE fmt utility oggex cmd cnc)

# Rename binary executable without -bin suffix
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME ${TARGET})

# Manual Installation
install(TARGETS ${BIN_NAME}
    DESTINATION bin
    COMPONENT bin)

# Compile experimental gui application
add_subdirectory(qt)
