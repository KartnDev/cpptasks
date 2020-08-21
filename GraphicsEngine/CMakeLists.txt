cmake_minimum_required(VERSION 3.16)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 17)


add_executable(GraphicsEngine main.cpp Vector3D.cpp Vector3D.hpp)
target_link_libraries(GraphicsEngine sfml-graphics sfml-window sfml-system)