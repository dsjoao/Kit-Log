cmake_minimum_required(VERSION 3.10)

project(KitTsp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../instances)

add_executable(tsp_run src/ILS.cpp src/Data.cpp src/ILS_Utils_bestImprovement.cpp src/ILS_Utils_construcao.cpp src/ILS_Utils_perturbacao.cpp src/main.cpp)

target_include_directories(tsp_run PRIVATE header)