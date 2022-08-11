set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION})
set(TARGET oggex)

# Make static, shared library
make_ssl(NAME ogx_cli
    SRCS cli.c
    HDRS ${HEADERS})

set(BIN_NAME oggex-bin)
add_executable(${BIN_NAME} oggex-bin.cpp)
target_include_directories(${BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${BIN_NAME} PRIVATE spdlog utility oggex ogx_cli)

# Rename binary executable without -bin suffix
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME ${TARGET})

# Manual Installation
install(TARGETS ${BIN_NAME}
    DESTINATION bin
    COMPONENT bin)

# Compile experimental gui application
add_subdirectory(qt)
