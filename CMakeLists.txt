cmake_minimum_required(VERSION 3.20)
project (Decimal)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
add_library(Decimal STATIC include/Decimal.h src/Decimal.cpp)
add_executable(test test/test.cpp)

target_link_libraries(test
        debug Decimal)