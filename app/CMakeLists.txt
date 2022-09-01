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

make_bin(
    NAME ${TARGET}
    SRCS main.cpp
    HDRS ${HEADERS}
    DEPS ${PKG_DEPENDS} oggex cli ogx)

# Manual Installation
install(TARGETS ${BIN_NAME} DESTINATION bin COMPONENT bin)

add_subdirectory(qt)
add_subdirectory(gtk)
#add_subdirectory(gtkmm)
