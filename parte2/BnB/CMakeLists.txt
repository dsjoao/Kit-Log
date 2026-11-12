cmake_minimum_required(VERSION 3.10)

project(KitBnB)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory("heuristic")

add_executable(BnB_run
							src/Data.cpp
							src/hungarian.cpp
							src/test.cpp
							src/BnB.cpp
							src/main.cpp)

target_include_directories(BnB_run PRIVATE include)
target_link_libraries(BnB_run PRIVATE tsp_lib)
target_compile_options(BnB_run PRIVATE
		-g
		-O0
    -Wall
    -Wextra
)
