file(GLOB MODELS_SRC
    *.hpp
    *.cpp)

add_library(${MODELS_LIB_NAME} STATIC ${MODELS_SRC})
