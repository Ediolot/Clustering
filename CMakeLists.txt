cmake_minimum_required(VERSION 3.19)
project(clustering)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

add_subdirectory(3rd_party/benchmark)

add_executable(clustering src/main.cpp src/math/vector_randomizer.h src/utils/plotter.cpp)
add_executable(clustering_benchmark src/benchmark.cpp src/math/vector_randomizer.h src/utils/plotter.cpp)
target_link_libraries(clustering_benchmark benchmark::benchmark)