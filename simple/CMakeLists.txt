cmake_minimum_required(VERSION 3.15)
project(simple)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(simple main.cpp Task.cpp Task.h Machine.cpp Machine.h)