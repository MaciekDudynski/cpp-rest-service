set(PLUGIN_NAME "test")

file(GLOB SRC
    *.hpp
    *.cpp)

add_library(${PLUGIN_NAME} MODULE ${SRC})

target_link_libraries(${PLUGIN_NAME} ${BASE_PLUGIN_NAME})
