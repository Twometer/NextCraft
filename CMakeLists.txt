cmake_minimum_required(VERSION 3.14)
project(NextCraft)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glm/glm)
add_subdirectory(lib/glfw)
add_subdirectory(lib/json)

add_executable(NextCraft
        src/net/TcpClient.cpp
        src/net/McClient.cpp
        src/net/McBuffer.cpp
        src/net/NetUtils.cpp
        src/util/ZLib.cpp
        src/chat/ChatParser.cpp
        src/model/Chunk.cpp
        src/model/World.cpp
        src/model/Section.cpp
        src/render/GameRenderer.cpp
        src/main.cpp
        ext/glad.c src/model/BlockData.h)

target_include_directories(NextCraft PRIVATE lib/glm lib/glfw/include inc)
target_link_libraries(NextCraft glfw ${GLFW_LIBRARIES} nlohmann_json::nlohmann_json Ws2_32.lib z.lib)