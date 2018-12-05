file(GLOB SRC
    *.hpp
    *.cpp)

add_library(${MODELS_LIB_NAME} STATIC ${SRC})
