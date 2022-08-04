set(HEADERS ${INCLUDES_DIR}  ${INCLUDES_DIR}/utility)
make_ssl(
    NAME oggex
    HDRS ${HEADERS}
    SRCS Oggex.cpp
    DEPS fmt utility image audio)

add_subdirectory(utility)
