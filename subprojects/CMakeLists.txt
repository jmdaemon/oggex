#set(UTILITY_LIBP subprojects/utility/build/release/lib)
#set(UTILITY_HEADERS subprojects/utility/include)
#set(UTILITY_LIB utility)

#add_library(${UTILITY_LIB} SHARED IMPORTED GLOBAL)
#set_target_properties(
    #${UTILITY_LIB}
    #PROPERTIES 
        #IMPORTED_LOCATION ${UTILITY_HEADERS}
        #IMPORTED_IMPLIB ${UTILITY_HEADERS}/${UTILITY_LIB}.so
#)


#find_library(${UTILITY_LIB}
             #NAMES ${UTILITY_LIB}
             #HINTS ${UTILITY_LIB})

#if(NOT libutility)
  #message(FATAL_ERROR "Utility library not found!")
#endif()

#if(NOT ${UTILITY_LIB})
  #message(FATAL_ERROR "Utility library not found!")
#endif()

#target_include_directories(${PROJECT_EXECUTABLE} PUBLIC ${UTILITY_HEADERS})
#target_link_libraries(${PROJECT_EXECUTABLE} utility)
