#include <glad/glad.h>
#include "NextCraft.h"

int main() {
    if (!NextCraft::Start()) {
        glfwTerminate();
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(NextCraft::window)) {

        glfwSwapBuffers(NextCraft::window);
        glfwPollEvents();
    }

    NextCraft::Shutdown();

    return 0;
}