cmake_minimum_required(VERSION 3.19)
project(Unit_tests)

add_executable(Unit_tests ${CMAKE_SOURCE_DIR}/include/invertedIndex.h
        ${CMAKE_SOURCE_DIR}/src/invertedIndex.cpp ${CMAKE_SOURCE_DIR}/include/searchServer.h
        ${CMAKE_SOURCE_DIR}/src/searchServer.cpp test.cpp)

target_include_directories(Unit_tests PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

FetchContent_MakeAvailable(googletest)
enable_testing()

target_link_libraries(Unit_tests PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(Unit_tests)


