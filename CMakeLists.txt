cmake_minimum_required(VERSION 3.14)
project(NextCraft)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(NextCraft
        src/net/TcpClient.cpp
        src/net/McClient.cpp
        src/net/McBuffer.cpp
        src/net/NetUtils.cpp
        src/util/ZLib.cpp
        src/chat/ChatParser.cpp
        src/main.cpp lib/concurrentqueue.h src/model/Player.h)

target_link_libraries(NextCraft Ws2_32.lib z.lib)