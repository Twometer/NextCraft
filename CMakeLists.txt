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
        src/net/chat/ChatParser.cpp
        src/util/ZLib.cpp
        src/util/Logger.cpp
        src/util/FloatBuffer.cpp
        src/model/world/Chunk.cpp
        src/model/world/World.cpp
        src/model/world/Section.cpp
        src/model/world/BlockData.cpp
        src/model/world/AABB.cpp
        src/model/block/BlockRegistry.cpp
        src/model/player/Player.cpp
        src/render/Camera.cpp
        src/render/GameRenderer.cpp
        src/render/shaders/IShader.cpp
        src/render/block/IBlockRenderer.cpp
        src/render/block/DefaultBlockRenderer.cpp
        src/render/block/PlantRenderer.cpp
        src/render/block/LeavesRenderer.cpp
        src/input/InputHandler.cpp
        src/input/Raycast.cpp
        src/render/HighlightRenderer.cpp
        src/mesh/AsyncMeshBuilder.cpp
        src/mesh/SectionMesh.cpp
        src/mesh/Mesh.cpp
        src/gl/Loader.cpp
        src/gl/Vao.cpp
        src/NextCraft.cpp
        src/main.cpp
        ext/glad.c
        ext/spng.c)

target_include_directories(NextCraft PRIVATE lib/glm lib/glfw/include inc)
target_link_libraries(NextCraft glfw ${GLFW_LIBRARIES} nlohmann_json::nlohmann_json Ws2_32.lib z.lib)