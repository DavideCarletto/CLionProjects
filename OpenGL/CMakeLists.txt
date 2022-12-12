cmake_minimum_required(VERSION 3.21)
project(OpenGL C)

set(CMAKE_C_STANDARD 99)

add_executable(OpenGL main.c)
target_link_libraries(OpenGL -lOpenGL32 -lfreeGLUT)