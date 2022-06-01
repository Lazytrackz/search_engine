cmake_minimum_required(VERSION 3.19)
project(Unit_tests)

add_executable(Unit_tests ${MY_INCLUDE_DIR}/invertedIndex.h ${MY_SRC_DIR}/invertedIndex.cpp
        ${MY_INCLUDE_DIR}/searchServer.h ${MY_SRC_DIR}/searchServer.cpp test.cpp)

target_include_directories(Unit_tests PUBLIC ${MY_INCLUDE_DIR} ${MY_SRC_DIR})

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


