cmake_minimum_required(VERSION 3.19)
project(clustering)

set(CMAKE_CXX_STANDARD 20)

add_executable(clustering src/main.cpp src/math/vector_randomizer.h src/utils/plotter.cpp)