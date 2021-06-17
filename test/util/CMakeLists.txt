# ================ Image Tests ================
set(TARGET testimage)
add_executable(${TARGET} ImageTests.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_17)
target_link_libraries(${TARGET} PRIVATE audio audio_library image_library file_library fmt doctest)

target_include_directories(${TARGET} PUBLIC ${DOCTEST_LIB})

add_test(NAME test_image COMMAND ${TARGET})

# ================ Audio Tests ================
set (AUDIO_TESTS testaudio)
add_executable(${AUDIO_TESTS} AudioTests.cpp)

target_compile_features(${AUDIO_TESTS} PRIVATE cxx_std_20)
target_link_libraries(${AUDIO_TESTS} PRIVATE audio audio_library file_library fmt doctest)
target_include_directories(${AUDIO_TESTS} PUBLIC ${DOCTEST_LIB})

add_test(NAME test_audio COMMAND ${AUDIO_TESTS})

# ================ Command Tests ================
#set (CMD_TESTS testcmd)
#add_executable(${CMD_TESTS} CmdTests.cpp)
#target_compile_features(${CMD_TESTS} PRIVATE cxx_std_20)

#target_link_libraries(${CMD_TESTS} PRIVATE audio_library image_library file_library fmt doctest)
#target_include_directories(${CMD_TESTS} PUBLIC ${DOCTEST_LIB})
#add_test(NAME test_cmd COMMAND ${CMD_TESTS})

# ================ Masking Tests ================
#set (MASK_TESTS testmask)
#add_executable(${MASK_TESTS} MaskTests.cpp)
#target_compile_features(${MASK_TESTS} PRIVATE cxx_std_20)


#target_link_libraries(${MASK_TESTS} PRIVATE audio_library image_library file_library fmt doctest)
#target_include_directories(${MASK_TESTS} PUBLIC ${DOCTEST_LIB})
#add_test(NAME test_mask COMMAND ${MASK_TESTS})
