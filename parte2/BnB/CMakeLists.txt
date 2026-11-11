cmake_minimum_required(VERSION 3.10)

project(KitBnB)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG -Wall -Wextra -Wconversion -Wsign-compare -Werror)

add_subdirectory("heuristic")

add_executable(BnB_run
							src/main.cpp
							src/Data.cpp
							src/hungarian.cpp)

target_include_directories(BnB_run PRIVATE include)
target_link_libraries(BnB_run PRIVATE tsp_lib)
