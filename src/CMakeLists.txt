set(HEADERS ${INCLUDES_DIR})
make_ssl(
    NAME oggex
    HDRS ${HEADERS}
    SRCS oggex.cpp ogxlog.cpp
    DEPS spdlog utility)
