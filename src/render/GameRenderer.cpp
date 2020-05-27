//
// Created by Twometer on 23 Jan 2020.
//

#include <glad/glad.h>
#include <iostream>
#include "GameRenderer.h"
#include "../NextCraft.h"
#include "../gl/Loader.h"
#include "../util/Logger.h"

void GameRenderer::Initialize() {
    glEnable(GL_DEPTH_TEST);
    glCheckErrors();

    glEnable(GL_CULL_FACE);
    glCheckErrors();

    glCullFace(GL_BACK);
    glCheckErrors();

    glEnable(GL_BLEND);
    glCheckErrors();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCheckErrors();

    glClearColor(0.72f, 0.83f, 0.996f, 1.0f);
    glCheckErrors();

    timer.Begin(60.0f);
    networkTimer.Begin(20.0f);

    this->terrainShader = new TerrainShader();
    this->terrainTexture = Loader::LoadTexture("assets/textures/atlas_blocks.png");
}

void GameRenderer::RenderFrame() {
    glViewport(0, 0, NextCraft::viewport.width, NextCraft::viewport.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);
    glCheckErrors();

    glm::mat4 matrix = camera.CalculateMatrix();
    terrainShader->Use();
    terrainShader->SetMatrix(matrix);
    terrainShader->SetTextureUnit(0);

    for (auto &pair : NextCraft::client->world.GetChunks()) {
        chunk::Chunk *chk = pair.second;
        if (chk == nullptr)
            continue;

        if (chk->fadeProgress < 100)
            chk->fadeProgress++;
        terrainShader->SetOpacity(chk->fadeProgress / 100.f);

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

    if (networkTimer.HasReached()) {
        if (NextCraft::client->IsReady()) {
            Player &player = NextCraft::client->player;
            NextCraft::client->SendPosLook(player.posX, player.posY, player.posZ, player.yaw, player.pitch, false);
        }
        networkTimer.Reset();
    }

    NextCraft::client->world.Cleanup();
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
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (0 != mouseX || 0 != mouseY) {
        player.yaw -= 0.125f * (float) mouseX;
        player.pitch -= 0.125f * (float) mouseY;

        player.pitch = glm::clamp(player.pitch, -90.f, 90.f);
        glfwSetCursorPos(window, 0, 0);
    }

    float yaw = glm::radians(player.yaw);
    glm::vec3 direction(glm::sin(yaw), 0, glm::cos(yaw));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.Move(direction * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm::vec3 directionLeft(direction.z, 0, -direction.x);
        player.Move(directionLeft * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player.Move(-direction * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm::vec3 directionRight(-direction.z, 0, direction.x);
        player.Move(directionRight * 0.5f);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player.Move(glm::vec3(0, 0.5, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        player.Move(glm::vec3(0, -0.5, 0));
    }
}
