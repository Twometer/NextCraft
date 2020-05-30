//
// Created by twome on 26/01/2020.
//
#include "NextCraft.h"
#include <crystal/CrystalUI.h>

McClient *NextCraft::client;
GLFWwindow *NextCraft::window;
Viewport NextCraft::viewport{};
bool NextCraft::isCursorCaught = true;

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
    glfwSetMouseButtonCallback(window, &(NextCraft::mouse_button_callback));
    glfwSetCharCallback(window, &(NextCraft::character_callback));
    glfwSetKeyCallback(window, &(NextCraft::key_callback));
    glfwSetCursorPosCallback(window, &(NextCraft::cursor_position_callback));

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
    crystal::CrystalUI::get_instance()->get_gui_renderer()->layout();
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

void NextCraft::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        crystal::CrystalUI::get_instance()->get_gui_renderer()->on_mouse_down(glm::vec2(mouseX, mouseY));
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        crystal::CrystalUI::get_instance()->get_gui_renderer()->on_mouse_up(glm::vec2(mouseX, mouseY));
}

void NextCraft::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    crystal::CrystalUI::get_instance()->get_gui_renderer()->on_key_event(key, action);
}

void NextCraft::character_callback(GLFWwindow *window, unsigned int codepoint) {
    crystal::CrystalUI::get_instance()->get_gui_renderer()->on_character_typed(codepoint);
}

void NextCraft::cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    crystal::CrystalUI::get_instance()->get_gui_renderer()->on_mouse_move(glm::vec2(xpos, ypos));
}

void NextCraft::SetCursorCaught(bool cursorCaught) {
    isCursorCaught = cursorCaught;
    if (cursorCaught)
        glfwSetInputMode(NextCraft::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    else
        glfwSetInputMode(NextCraft::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool NextCraft::IsCursorCaught() {
    return isCursorCaught;
}
