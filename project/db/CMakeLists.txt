include_directories(../cfg ../models)

file(GLOB SRC
    *.hpp
    *.cpp)

add_library(${DB_LIB_NAME} STATIC ${SRC})

target_link_libraries(${DB_LIB_NAME} cfg models)
