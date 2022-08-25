set(HEADERS ${INCLUDES_DIR} ${jolly_SOURCE_DIR}/include)
set(TARGET oggex)
make_ssl(
    NAME ${TARGET}
    HDRS ${HEADERS}
    SRCS oggex.cpp
    DEPS ${PKG_DEPENDS})

# Installation targets
install(TARGETS ${TARGET}
    DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT lib)

install(TARGETS ${TARGET}_static
    DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT lib)
