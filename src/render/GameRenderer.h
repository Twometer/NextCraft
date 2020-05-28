//
// Created by Twometer on 23 Jan 2020.
//

#ifndef NEXTCRAFT_GAMERENDERER_H
#define NEXTCRAFT_GAMERENDERER_H

#include "shaders/TerrainShader.h"
#include "shaders/HighlightShader.h"
#include "Camera.h"
#include "../util/Timer.h"
#include "../pick/Raycast.h"
#include "../pick/HighlightRenderer.h"

class GameRenderer {
private:
    Camera camera{};
    Timer inputTimer;
    Timer networkTimer;

    TerrainShader *terrainShader;
    HighlightShader *highlightShader;
    GLuint terrainTexture;

    Raycast raycast = Raycast(4.2f, 0.005f);
    RaycastResult lookingAt;
    HighlightRenderer highlightRenderer;
public:
    void Initialize();

    void RenderFrame();

private:
    void HandleInput();

};


#endif //NEXTCRAFT_GAMERENDERER_H
