//
// Created by Twometer on 23 Jan 2020.
//

#include <glad/glad.h>
#include <iostream>
#include "GameRenderer.h"
#include "../NextCraft.h"
#include "../gl/Loader.h"

void GameRenderer::Initialize() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    timer.Begin(60.0f);

    this->terrainShader = new TerrainShader();
    this->terrainTexture = Loader::LoadTexture("assets/textures/atlas_blocks.png");
}

void GameRenderer::RenderFrame() {
    glViewport(0, 0, NextCraft::viewport.width, NextCraft::viewport.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);

    glm::mat4 matrix = camera.CalculateMatrix();
    terrainShader->Use();
    terrainShader->SetMatrix(matrix);

    for (auto &pair : NextCraft::client->world.GetChunks()) {
        chunk::Chunk *chk = pair.second;
        for (int i = 0; i < 16; i++) {
            chunk::Section *section = chk->GetSection(i);
            if (section != nullptr)
                section->mesh->Render();
        }
    }

    if (timer.HasReached()) {
        HandleTick();
        timer.Reset();
    }
}

void GameRenderer::HandleTick() {
    HandleInput();
}

void GameRenderer::HandleInput() {
    GLFWwindow *window = NextCraft::window;
    Player &player = NextCraft::client->player;

    bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
    if (!focused) return;

    double mouseX, mouseY;
    static double mouseXLast, mouseYLast;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (mouseXLast != mouseX || mouseYLast != mouseY) {
        player.yaw -= 0.2f * (mouseX - mouseXLast);
        player.pitch += 0.2f * (mouseY - mouseYLast);

        player.pitch = glm::clamp(player.pitch, -90.f, 90.f);

        mouseXLast = mouseX;
        mouseYLast = mouseY;

        glfwSetCursorPos(window, 200, 200);
    }

    float yaw = glm::radians(player.yaw);
    glm::vec3 direction(glm::sin(yaw), 0, glm::cos(yaw));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.Move(direction * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player.Move(-direction * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player.Move(glm::vec3(0, 0.5, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        player.Move(glm::vec3(0, -0.5, 0));
    }
}
