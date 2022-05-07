cmake_minimum_required(VERSION 3.19)
project(search_engine_V.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CURRENT_VERSION 1.0)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
configure_file (${MY_INCLUDE_DIR}/config.h.in ${MY_INCLUDE_DIR}/config.h @ONLY)

set(JSON_BuildTests OFF CASH INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(search_engine src/converter.cpp include/converter.h include/index.h src/index.cpp
        include/searchServer.h src/searchServer.cpp src/main.cpp)

target_include_directories(search_engine PUBLIC include)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)



































