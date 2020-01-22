//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_NEXTCRAFT_H
#define NEXTCRAFT_NEXTCRAFT_H

#include <GLFW/glfw3.h>
#include <thread>
#include "net/McClient.h"

class NextCraft {
private:
    static void Connect() {
        client->Connect("DevClient", "localhost", 25565);
    }

public:
    static McClient *client;

    static GLFWwindow *window;

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

        window = glfwCreateWindow(1000, 700, "NextCraft", nullptr, nullptr);
        if (!window) {
            return false;
        }
        glfwMakeContextCurrent(window);

        new std::thread(&NextCraft::Connect);
        return true;
    }

    static void Shutdown() {
        client->Disconnect();
    }

};

McClient *NextCraft::client;
GLFWwindow *NextCraft::window;

#endif //NEXTCRAFT_NEXTCRAFT_H
