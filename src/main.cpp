#include <glad/glad.h>
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

    while (!glfwWindowShouldClose(NextCraft::window)) {
        renderer.RenderFrame();
        glfwSwapBuffers(NextCraft::window);
        glfwPollEvents();
    }

    NextCraft::Shutdown();

    return 0;
}