# ================ File Library ================
# Add both shared and static library targets
make_static_shared_lib(
    NAME file
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR}
    SOURCES File.cpp
    DEPS fmt)

# ================ Image Library ================
make_static_shared_lib(
    NAME image
    CSTANDARD cxx_std_11
    HEADERS ${UTILITY_DIR}
    SOURCES Image.cpp
    DEPS fmt)

# ================ Audio Library ================
make_static_shared_lib(
    NAME audio_library
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Audio.cpp Mask.cpp
    DEPS fmt image)

# ================ Command Library ================
make_static_shared_lib(
    NAME cmd
    CSTANDARD ${CSTANDARD}
    HEADERS ${UTILITY_DIR} ${AUDIO_DIR}
    SOURCES Data.cpp Cmd.cpp InputParser.cpp
    DEPS fmt)
