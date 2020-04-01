//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_TERRAINSHADER_H
#define NEXTCRAFT_TERRAINSHADER_H

#include "IShader.h"

class TerrainShader : public IShader {
private:
    GLuint loc_matrix;

public:
    TerrainShader() {
        Initialize("terrain");
    }

    void BindUniforms() override {
        loc_matrix = GetLocation("matrix");
    }

    void SetMatrix(const glm::mat4 &matrix) {
        LoadMatrix(loc_matrix, matrix);
    }

};

#endif //NEXTCRAFT_TERRAINSHADER_H
