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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.72f, 0.83f, 0.996f, 1.0f);

    inputTimer.Begin(60.0f);
    networkTimer.Begin(20.0f);

    this->terrainShader = new TerrainShader();
    this->highlightShader = new HighlightShader();
    this->terrainTexture = Loader::LoadTexture("assets/textures/atlas_blocks.png");
}

void GameRenderer::RenderFrame() {
    glViewport(0, 0, NextCraft::GetViewport().width, NextCraft::GetViewport().height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);

    camera.CalculateMatrix();

    terrainShader->Use();
    terrainShader->SetViewMatrix(camera.GetViewMatrix());
    terrainShader->SetProjectionMatrix(camera.GetProjectionMatrix());
    terrainShader->SetSkyColor(glm::vec3(0.72f, 0.83f, 0.996f));
    terrainShader->SetBrightness(1.0f);
    terrainShader->SetTextureUnit(0);

    for (auto &pair : NextCraft::GetWorld().GetChunks()) {
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

    glDisable(GL_CULL_FACE);
    highlightShader->Use();
    highlightShader->SetViewMatrix(camera.GetViewMatrix());
    highlightShader->SetProjectionMatrix(camera.GetProjectionMatrix());
    highlightShader->SetOffset(inputHandler.GetLookingAt().blockPosition);
    highlightShader->SetSize(glm::vec3(1.0f, 1.0f, 1.0f));
    highlightRenderer.Render();
    glEnable(GL_CULL_FACE);

    if (inputTimer.HasReached()) {
        inputHandler.HandleInput();
        inputTimer.Reset();
    }

    if (networkTimer.HasReached()) {
        if (NextCraft::GetClient().IsReady()) {
            Player &player = NextCraft::GetPlayer();
            NextCraft::GetClient().SendPosLook(player.posX, player.posY, player.posZ, player.yaw, player.pitch,
                                               player.onGround);
        }
        networkTimer.Reset();
    }

    NextCraft::GetWorld().Cleanup();
}
