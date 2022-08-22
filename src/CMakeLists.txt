set(HEADERS ${INCLUDES_DIR} ${jolly_SOURCE_DIR}/include)
make_ssl(
    NAME oggex
    HDRS ${HEADERS}
    SRCS oggex.cpp
    DEPS spdlog utility jolly)
