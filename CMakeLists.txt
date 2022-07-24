cmake_minimum_required(VERSION 3.21)
project(utils C)

set(CMAKE_C_STANDARD 23)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_compile_options(-g -Wall -lm -ldl -fPIC -rdynamic)
add_library(utils SHARED ${SOURCE_FILES})
