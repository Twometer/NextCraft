//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_TERRAINSHADER_H
#define NEXTCRAFT_TERRAINSHADER_H

#include "IShader.h"

class TerrainShader : public IShader {
private:
    GLuint loc_matrix;
    GLuint loc_texture;

public:
    TerrainShader() {
        Initialize("terrain");
    }

    void BindUniforms() override {
        loc_matrix = GetLocation("matrix");
        loc_texture = GetLocation("tex");
    }

    void SetMatrix(const glm::mat4 &matrix) {
        LoadMatrix(loc_matrix, matrix);
    }

    void SetTextureUnit(const int idx) {
        glUniform1i(loc_texture, idx);
    }

};

#endif //NEXTCRAFT_TERRAINSHADER_H
