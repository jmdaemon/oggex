# ================ Command Library ================
#set(FILE_LIBRARY_HEADERS "${OGGEX_SOURCE_DIR}/include/util")
set(TARGET command)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE command.c
    #PUBLIC  ${FILE_LIBRARY_HEADERS}
)

#target_include_directories(${TARGET} PUBLIC ${FILE_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  )
  #FILES ${FILE_LIBRARY_HEADERS})
  
# ================ File Library ================
set(TARGET file)

add_library(${TARGET})
target_sources(${TARGET}
    PRIVATE file.c
    #PUBLIC  ${FILE_LIBRARY_HEADERS}
)

#target_include_directories(${TARGET} PUBLIC ${FILE_LIBRARY_HEADERS})
target_link_libraries(${TARGET} PRIVATE fmt)
target_compile_features(${TARGET} PUBLIC cxx_std_20)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  )
