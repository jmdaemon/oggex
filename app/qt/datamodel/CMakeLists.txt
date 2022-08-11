#set(QT_HEADERS "${PROJECT_SOURCE_DIR}/app/qt/datamodel")
set(TARGET datamodel)

# Manually include headers
qt6_wrap_cpp(HEADER ${QT_HEADERS}/datamodel.h)

add_library(${TARGET} datamodel.cpp ${HEADER})

#target_sources(${TARGET}
    #PRIVATE datamodel.cpp
    #PUBLIC  ${QT_HEADERS})



#add_executable(hello-world MainWindow.cpp main.cpp
               #${hello-world_UI} ${hello-world_SRC})
#qt5_use_modules(hello-world Widgets)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_include_directories(${TARGET} PUBLIC ${QT_HEADERS})
target_link_libraries(${TARGET} PRIVATE Qt6::Widgets)
#target_compile_features(${TARGET} PUBLIC cxx_std_20)

#source_group(
  #TREE "${PROJECT_SOURCE_DIR}/app/qt"
  #PREFIX "Header Files"
  #FILES ${QT_HEADERS})
