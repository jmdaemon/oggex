# Samples
set(SAMPLES_DIR samples)
set(SAMPLE_FILES
    ${SAMPLES_DIR}/extract/835127a09fc542aeb3bfa99c9d91972d.png     # Image + Audio + Tags (embedded)
    ${SAMPLES_DIR}/embed/835127a09fc542aeb3bfa99c9d91972d.png.png   # Image + Image Tag
    ${SAMPLES_DIR}/embed/audio02.ogg)                               # Audio + Sound Tag

# Copy samples to build directory
file(COPY samples DESTINATION ${CMAKE_BINARY_DIR})
