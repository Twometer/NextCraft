//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_TERRAINSHADER_H
#define NEXTCRAFT_TERRAINSHADER_H

#include "IShader.h"

class TerrainShader : public IShader {
private:
    GLuint loc_modelMatrix;
    GLuint loc_cameraMatrix;

public:
    TerrainShader() {
        Initialize("terrain");
    }

    void BindUniforms() override {
        loc_modelMatrix = GetLocation("modelMatrix");
        loc_cameraMatrix = GetLocation("cameraMatrix");
    }

    void SetModelMatrix(const glm::mat4 &matrix) {
        LoadMatrix(loc_modelMatrix, matrix);
    }

    void SetCameraMatrix(const glm::mat4 &matrix) {
        LoadMatrix(loc_cameraMatrix, matrix);
    }

};

#endif //NEXTCRAFT_TERRAINSHADER_H
