#define CRYSTALUI_DEBUGLOG false

#include <glad/glad.h>
#include <iostream>
#include "NextCraft.h"
#include "render/GameRenderer.h"

int main() {
    if (!NextCraft::Start()) {
        glfwTerminate();
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return 1;
    }

    GameRenderer renderer{};
    renderer.Initialize();

    GLFWwindow *window = NextCraft::window;

    while (!glfwWindowShouldClose(window)) {
        renderer.RenderFrame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    NextCraft::Shutdown();

    return 0;
}
