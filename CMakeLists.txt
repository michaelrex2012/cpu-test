cmake_minimum_required(VERSION 4.0)
project(CPU-Test)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPU-Test main.cpp
        color.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
target_link_libraries(CPU-Test PRIVATE ${CMAKE_DL_LIBS} -static -lpthread)
