cmake_minimum_required(VERSION 3.28)
project(sabr2 C)

set(CMAKE_C_STANDARD 90)

add_executable(sabr2 main.c sabr.c
        sabr_builtins.c)
target_compile_options(sabr2 PUBLIC -Wall -Wextra -static -static-libgcc)

