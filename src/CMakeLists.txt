cmake_minimum_required(VERSION 3.19)

add_executable(Search_engine converterJSON.cpp ${CMAKE_SOURCE_DIR}/include/converterJSON.h
        ${CMAKE_SOURCE_DIR}/include/invertedIndex.h invertedIndex.cpp
        ${CMAKE_SOURCE_DIR}/include/searchServer.h searchServer.cpp main.cpp)

target_include_directories(Search_engine PUBLIC ${CMAKE_SOURCE_DIR}/include)