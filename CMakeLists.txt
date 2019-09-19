cmake_minimum_required(VERSION 3.14)
project(NextCraft)

set(CMAKE_CXX_STANDARD 14)

add_executable(NextCraft
        src/net/McBuffer.cpp
        src/net/NetUtils.cpp
        src/main.cpp)