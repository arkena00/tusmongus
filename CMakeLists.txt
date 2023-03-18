cmake_minimum_required(VERSION 3.24)
project(amodus)

set(CMAKE_CXX_STANDARD 17)

add_library(amodus SHARED source/main.cpp)

target_link_directories(amodus PUBLIC api)
target_link_libraries(amodus PUBLIC arkena_mod)
target_include_directories(amodus PUBLIC api/include)