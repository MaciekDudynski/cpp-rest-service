cmake_minimum_required(VERSION 3.0.0)

project(cpp-rest-service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wconversion -pedantic -Wno-unknown-pragmas -fPIC")

include_directories(.)

set(CONFIG_LIB_NAME "cfg")
set(MODELS_LIB_NAME "models")
set(DB_LIB_NAME "db")

add_subdirectory(cfg)
add_subdirectory(models)
add_subdirectory(controllers)
add_subdirectory(db)
add_subdirectory(core)
