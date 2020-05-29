//
// Created by Twometer on 23 Jan 2020.
//

#ifndef NEXTCRAFT_GAMERENDERER_H
#define NEXTCRAFT_GAMERENDERER_H

#include "shaders/TerrainShader.h"
#include "shaders/HighlightShader.h"
#include "Camera.h"
#include "../util/Timer.h"
#include "../input/InputHandler.h"
#include "HighlightRenderer.h"
#include "RenderLayer.h"

class GameRenderer {
private:
    Camera camera{};
    InputHandler inputHandler{};

    Timer inputTimer;
    Timer networkTimer;

    TerrainShader *terrainShader;
    HighlightShader *highlightShader;
    GLuint terrainTexture;

    HighlightRenderer highlightRenderer;

public:
    void Initialize();

    void RenderFrame();

    void RenderWorld(RenderLayer layer);

};


#endif //NEXTCRAFT_GAMERENDERER_H
