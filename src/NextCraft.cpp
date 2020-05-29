//
// Created by twome on 26/01/2020.
//
#include "NextCraft.h"

McClient *NextCraft::client;
GLFWwindow *NextCraft::window;
Viewport NextCraft::viewport{};

bool NextCraft::Start() {
    client = new McClient();

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1000, 700, GAME_TITLE, nullptr, nullptr);
    if (!window) {
        return false;
    }

    glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
    glfwGetWindowContentScale(window, &viewport.scaleX, &viewport.scaleY);
    glfwSetFramebufferSizeCallback(window, &(NextCraft::framebuffer_size_callback));

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);

    new std::thread(&NextCraft::Connect);

    BlockRegistry::Initialize();
    AsyncMeshBuilder::Initialize();
    return true;
}

void NextCraft::Shutdown() {
    client->Disconnect();
    delete client;
    glfwTerminate();
}

void NextCraft::Connect() {
    client->Connect("DevClient", "localhost", 25565);
}

void NextCraft::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    viewport.width = width;
    viewport.height = height;
}

World &NextCraft::GetWorld() {
    return client->world;
}

Player &NextCraft::GetPlayer() {
    return client->player;
}

McClient &NextCraft::GetClient() {
    return *client;
}

const Viewport &NextCraft::GetViewport() {
    return viewport;
}
