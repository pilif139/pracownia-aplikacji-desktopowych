cmake_minimum_required(VERSION 3.16)
project(hello_window VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

ADD_COMPILE_DEFINITIONS(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(hello_window
    src/config.h
    src/main.cpp
    src/glad.c
    src/triangle_mesh.cpp
    src/square_mesh.cpp
    src/shader.cpp
    src/cube_mesh.cpp
    src/stb_image.cpp
)

target_include_directories(hello_window PRIVATE dependencies)

target_link_libraries(hello_window glfw OpenGL::GL)
