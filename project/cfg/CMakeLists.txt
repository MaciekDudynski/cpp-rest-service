configure_file(Configuration.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/Configuration.cpp)

file(GLOB CFG_SRC
    *.hpp
    *.cpp)

add_library(${CFG_LIB_NAME} STATIC ${CFG_SRC})
