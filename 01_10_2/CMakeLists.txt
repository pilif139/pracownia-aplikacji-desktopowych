cmake_minimum_required(VERSION 4.0)
project(01_10_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(01_10_2 main.c
        linked_list.c
        linked_list.h
        queue.c
        queue.h
)
