cmake_minimum_required(VERSION 3.12)
project(obj2stl VERSION 1.0.0)

set (CMAKE_CXX_STANDARD 14)

include_directories(include/obj2stl)

file(GLOB source_files
            "include/obj2stl/*.h"
            "src/obj2stl/*.cpp"
    )

add_library(libobj2stl ${source_files})

add_executable(obj2stl src/main.cpp)

target_link_libraries(obj2stl PRIVATE libobj2stl)
