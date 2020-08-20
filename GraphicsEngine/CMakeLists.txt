cmake_minimum_required(VERSION 3.16)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 14)


add_executable(GraphicsEngine main.cpp)
target_link_libraries(GraphicsEngine sfml-graphics sfml-window sfml-system)