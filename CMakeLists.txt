cmake_minimum_required(VERSION 3.8)
project(FAKTURY)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES pietralik_projekt.c structures.h lista_zamowienia.c lista_zamowienia.h)
add_executable(FAKTURY ${SOURCE_FILES})