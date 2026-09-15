cmake_minimum_required(VERSION 3.10)

project(KitMlp)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

add_executable(mlp_run scr/main.cpp scr/Data.cpp scr/MLP.cpp scr/MLP_Utils_bestImprovement.cpp scr/MLP_Utils_construcao.cpp scr/MLP_Utils_perturbacao.cpp)

target_include_directories(mlp_run PRIVATE header)
