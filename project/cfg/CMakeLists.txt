configure_file(Configuration.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/Configuration.cpp)

file(GLOB SRC
    *.hpp
    *.cpp)

add_library(${CONFIG_LIB_NAME} STATIC ${SRC})
