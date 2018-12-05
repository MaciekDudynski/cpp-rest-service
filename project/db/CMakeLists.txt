file(GLOB DB_SRC
    *.hpp
    *.cpp)

add_library(${DB_LIB_NAME} STATIC ${DB_SRC})

target_link_libraries(${DB_LIB_NAME} ${CFG_LIB_NAME})
