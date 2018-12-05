cmake_minimum_required(VERSION 3.0.0)

project(cpp-rest-service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wconversion -pedantic -Wno-unknown-pragmas")

find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
find_package(Threads REQUIRED)
find_package(OpenSSL 1.0.1 REQUIRED)
find_package(cpprestsdk REQUIRED)
#find_package(pqxx REQUIRED)

configure_file(config/Configuration.hpp.in ${CMAKE_SOURCE_DIR}/include/utils/Configuration.hpp)

file(GLOB RestService_SRC
    include/*.hpp
    include/db/*.hpp
    include/utils/*.hpp
    include/controllers/*.hpp
    include/models/*.hpp
    src/*.cpp
    src/db/*.cpp
    src/utils/*.cpp
    src/controllers/*.cpp
    src/models/*.cpp)
add_executable(${PROJECT_NAME} ${RestService_SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} boost_system ssl crypto pthread cpprest pqxx)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
