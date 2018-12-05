set(LIB_NAME "base")

file(GLOB SRC
    *.hpp
    *.cpp
    utils/*.hpp
    utils/*.cpp)

add_library(${LIB_NAME} STATIC ${SRC})

target_link_libraries(${LIB_NAME} db)
