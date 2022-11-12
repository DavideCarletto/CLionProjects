cmake_minimum_required(VERSION 3.21)
project(09knapsack_no_pruning C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(09knapsack_no_pruning
        Item.c
        Item.h
        main.c)
