cmake_minimum_required(VERSION 3.12)
project(c_ex3 C)

set(CMAKE_C_STANDARD 99)

add_executable(c_ex3 infi.c NumericalAnalyzer.c)
target_link_libraries(c_ex3 m)
