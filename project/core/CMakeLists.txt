find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
find_package(Threads REQUIRED)
find_package(OpenSSL 1.0.1 REQUIRED)
find_package(cpprestsdk REQUIRED)
#find_package(pqxx REQUIRED)

file(GLOB CORE_SRC
    *.hpp
    utils/*.hpp
    *.cpp
    utils/*.cpp)

add_executable(${PROJECT_NAME} ${CORE_SRC})

target_link_libraries(${PROJECT_NAME} boost_system ssl crypto pthread cpprest pqxx ${DB_LIB_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION .)

