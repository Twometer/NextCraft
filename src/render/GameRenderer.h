//
// Created by Twometer on 23 Jan 2020.
//

#ifndef NEXTCRAFT_GAMERENDERER_H
#define NEXTCRAFT_GAMERENDERER_H


#include "shaders/TerrainShader.h"
#include "Camera.h"

class GameRenderer {
private:

    Camera camera;

    TerrainShader *terrainShader;
    GLuint terrainTexture;


public:
    void Initialize();

    void RenderFrame();

};


#endif //NEXTCRAFT_GAMERENDERER_H
