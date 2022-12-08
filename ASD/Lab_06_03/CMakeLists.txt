cmake_minimum_required(VERSION 3.21)
project(E3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(E3
        equipArray.h
        gdr.c
        inv.h inv.c
        invArray.h
        pg.h
        pgList.h invArray.c equipArray.c pg.c pgList.c)
