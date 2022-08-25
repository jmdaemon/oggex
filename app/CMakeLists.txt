set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${jolly_SOURCE_DIR}/include)
set(TARGET oggex)

# Make static, shared library
make_ssl(NAME cli
    SRCS cli.c
    HDRS ${HEADERS})

# Export a common ogx interface for use in oggex-bin, oggex-qt
make_ssl(NAME ogx
    SRCS oggex-bin.cpp
    HDRS ${HEADERS}
    DEPS ${PKG_DEPENDS} cli oggex)

set(BIN_NAME oggex-bin)
add_executable(${BIN_NAME} main.cpp)
target_include_directories(${BIN_NAME} PUBLIC ${HEADERS})
target_link_libraries(${BIN_NAME} PRIVATE ${PKG_DEPENDS} oggex cli ogx)

# Rename binary executable without -bin suffix
set_target_properties(${BIN_NAME} PROPERTIES OUTPUT_NAME ${TARGET})

# Manual Installation
install(TARGETS ${BIN_NAME}
    DESTINATION bin
    COMPONENT bin)

# Compile experimental gui application
add_subdirectory(qt)
