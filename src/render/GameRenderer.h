//
// Created by Twometer on 23 Jan 2020.
//

#ifndef NEXTCRAFT_GAMERENDERER_H
#define NEXTCRAFT_GAMERENDERER_H


#include "shaders/TerrainShader.h"

class GameRenderer {
private:

    TerrainShader *terrainShader;
    GLuint terrainTexture;


public:
    void Initialize();

    void RenderFrame();

};


#endif //NEXTCRAFT_GAMERENDERER_H
