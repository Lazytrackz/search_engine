cmake_minimum_required(VERSION 3.19)

add_executable(Search_engine converterJSON.cpp ${MY_INCLUDE_DIR}/converterJSON.h ${MY_INCLUDE_DIR}/invertedIndex.h
               invertedIndex.cpp ${MY_INCLUDE_DIR}/searchServer.h searchServer.cpp main.cpp)

target_include_directories(Search_engine PUBLIC ${MY_INCLUDE_DIR})