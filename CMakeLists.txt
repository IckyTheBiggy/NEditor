cmake_minimum_required(VERSION 3.10)
project(SmoothEditor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(SmoothEditor
    src/Cursor.cpp
    src/main.cpp
    src/Editor.cpp
    src/InputController
)

target_include_directories(SmoothEditor PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(SmoothEditor PRIVATE raylib)