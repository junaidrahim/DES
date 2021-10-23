cmake_minimum_required(VERSION 3.20)
project(DES)

set(CMAKE_CXX_STANDARD 17)

add_executable(DES main.cpp src/round_key.cpp src/round_key.h src/DES.cpp src/DES.h)
