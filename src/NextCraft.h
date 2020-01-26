//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_NEXTCRAFT_H
#define NEXTCRAFT_NEXTCRAFT_H

#include <thread>
#include "net/McClient.h"
#include <GLFW/glfw3.h>

#define GAME_TITLE "NextCraft 0.1.0"

struct Viewport {
    int width;
    int height;
    float scaleX;
    float scaleY;
};

class NextCraft {
private:
    static void Connect() {
        client->Connect("DevClient", "localhost", 25565);
    }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        viewport.width = width;
        viewport.height = height;
    }

public:
    static McClient *client;

    static GLFWwindow *window;

    static Viewport viewport;

    static bool Start() {
        client = new McClient();

        if (!glfwInit()) {
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        window = glfwCreateWindow(1000, 700, GAME_TITLE, nullptr, nullptr);
        if (!window) {
            return false;
        }

        glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
        glfwGetWindowContentScale(window, &viewport.scaleX, &viewport.scaleY);
        glfwSetFramebufferSizeCallback(window, &(NextCraft::framebuffer_size_callback));

        glfwMakeContextCurrent(window);

        new std::thread(&NextCraft::Connect);
        return true;
    }

    static void Shutdown() {
        client->Disconnect();
    }

};

#endif //NEXTCRAFT_NEXTCRAFT_H
