#
# Samples
# 
# Test out oggex using these files
set(SAMPLES_DIR samples)

# ${SAMPLE_FILES} isn't used for anything, 
# it is only here to describe what each file represents.
set(SAMPLE_FILES
    ${SAMPLES_DIR}/835127a09fc542aeb3bfa99c9d91972d.png         # Image + Audio + Tags (embedded)
    ${SAMPLES_DIR}/835127a09fc542aeb3bfa99c9d91972d.png.png     # Image + Image Tag
    ${SAMPLES_DIR}/audio02.ogg)                                 # Audio + Sound Tag

# Copy samples to build directory
file(COPY samples DESTINATION ${CMAKE_BINARY_DIR})
