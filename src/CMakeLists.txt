set(HEADERS ${INCLUDES_DIR}  ${INCLUDES_DIR}/utility)
make_ssl(
    NAME oggex
    HDRS ${HEADERS}
    SRCS oggex.cpp
    DEPS fmt utility)

add_subdirectory(utility)
