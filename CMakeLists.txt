cmake_minimum_required(VERSION 3.8)
project(FAKTURY)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c structures.h list.c list.h)
add_executable(FAKTURY ${SOURCE_FILES})