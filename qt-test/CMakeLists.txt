cmake_minimum_required(VERSION 3.16)
project(qt_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

# Create executable
add_executable(qt_test main.cpp)

# Link Qt libraries
target_link_libraries(qt_test
        PRIVATE Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
)