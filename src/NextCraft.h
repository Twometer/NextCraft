//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_NEXTCRAFT_H
#define NEXTCRAFT_NEXTCRAFT_H

#include "model/block/BlockRegistry.h"
#include "net/McClient.h"
#include "mesh/AsyncMeshBuilder.h"
#include <GLFW/glfw3.h>
#include <thread>

#define GAME_TITLE "NextCraft 0.1.0"

struct Viewport {
    int width;
    int height;
    float scaleX;
    float scaleY;
};

class NextCraft {
private:
    static void Connect();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

public:
    static McClient *client;

    static GLFWwindow *window;

    static Viewport viewport;

    static bool Start();

    static void Shutdown();

};

#endif //NEXTCRAFT_NEXTCRAFT_H
