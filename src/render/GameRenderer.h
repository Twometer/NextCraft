//
// Created by Twometer on 23 Jan 2020.
//

#ifndef NEXTCRAFT_GAMERENDERER_H
#define NEXTCRAFT_GAMERENDERER_H


#include "shaders/TerrainShader.h"
#include "Camera.h"
#include "../util/Timer.h"

class GameRenderer {
private:

    Camera camera;
    Timer timer;
    Timer networkTimer;

    TerrainShader *terrainShader;
    GLuint terrainTexture;


public:
    void Initialize();

    void RenderFrame();

private:
    void HandleTick();

    void HandleInput();

};


#endif //NEXTCRAFT_GAMERENDERER_H
