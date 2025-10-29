cmake_minimum_required(VERSION 4.0)
project(08_10_2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(08_10_2025 main.cpp
        PPMImage.cpp
        PPMImage.h
        PBMImage.cpp
        PBMImage.h
        PGMImage.cpp
        PGMImage.h
)
