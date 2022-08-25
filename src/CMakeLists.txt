set(HEADERS ${INCLUDES_DIR} ${jolly_SOURCE_DIR}/include)
set(TARGET oggex)
make_ssl(
    NAME ${TARGET}
    HDRS ${HEADERS}
    SRCS oggex.cpp
    DEPS ${PKG_DEPENDS})

# Installation targets
ilibs(TARGETS ${TARGET} ${TARGET}_static COMPS lib lib_static)
