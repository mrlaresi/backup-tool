cmake_minimum_required(VERSION 3.10)

# project name and version
project(Backuptool VERSION 0.2)

# c++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)

add_executable(Backuptool src/main.cpp 
    src/core.cpp
    src/basecommand.cpp 
    src/commands.cpp 
    src/fileinout.cpp
    src/invoker.cpp
    src/nogui.cpp
    src/validator.cpp)