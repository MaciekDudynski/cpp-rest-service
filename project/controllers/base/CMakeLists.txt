file(GLOB BASE_CONTROLLER_SRC
    *.hpp
    *.cpp
    utils/*.hpp
    utils/*.cpp)

add_library(${BASE_CONTROLLER_LIB_NAME} STATIC ${BASE_CONTROLLER_SRC})

target_link_libraries(${BASE_CONTROLLER_LIB_NAME} db)
