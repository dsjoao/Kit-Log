cmake_minimum_required(VERSION 3.10)

project(KitTsp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


add_library(tsp_lib src/ILS.cpp
src/Data.cpp src/ILS_Utils_bestImprovement.cpp
src/ILS_Utils_construcao.cpp src/ILS_Utils_perturbacao.cpp src/main.cpp)

target_include_directories(tsp_lib PUBLIC header)
