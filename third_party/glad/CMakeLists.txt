cmake_minimum_required(VERSION 3.25)
project(glad)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

add_library(glad ./src/glad.c)
target_include_directories(glad PUBLIC ./include/)

