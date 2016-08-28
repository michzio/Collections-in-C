cmake_minimum_required(VERSION 3.5)
project(collections)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c hash_map/hash_map.h hash_map/hash_map.c)
add_executable(collections ${SOURCE_FILES})