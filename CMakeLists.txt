cmake_minimum_required(VERSION 3.19)
project(Search_engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
configure_file(${MY_INCLUDE_DIR}/versionConfig.h.in ${MY_INCLUDE_DIR}/versionConfig.h)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(Search_engine PRIVATE nlohmann_json::nlohmann_json)



































