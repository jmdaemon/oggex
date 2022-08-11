#set(HEADERS ${INCLUDES_DIR} ${HEADERS_VERSION} ${INCLUDES_DIR}/utility)
set(HEADERS ${INCLUDES_DIR} ${INCLUDES_DIR}/utility)

# Add both shared and static library targets
#make_ssl(NAME audio
    ##SRCS Audio.cpp Mask.cpp
    #SRCS Audio.cpp
    #HDRS ${HEADERS}
    #HDR ${UTILITY_DIR}/Audio.h
    #DEPS fmt utility)

#make_ssl(NAME cmd
    #SRCS Data.cpp Cmd.cpp
    #HDRS ${HEADERS}
    #HDR ${UTILITY_DIR}/Cmd.h
    #DEPS fmt cnc utility bytesize)
