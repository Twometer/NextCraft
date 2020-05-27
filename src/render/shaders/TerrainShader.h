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
    GLuint loc_opacity;

public:
    TerrainShader() {
        Initialize("terrain");
    }

    void BindUniforms() override {
        loc_matrix = GetLocation("matrix");
        loc_opacity = GetLocation("opacity");
        loc_texture = GetLocation("tex");
    }

    void SetOpacity(float opacity) const {
        glUniform1f(loc_opacity, opacity);
    }

    void SetMatrix(const glm::mat4 &matrix) const {
        LoadMatrix(loc_matrix, matrix);
    }

    void SetTextureUnit(const int idx) const {
        glUniform1i(loc_texture, idx);
    }

};

#endif //NEXTCRAFT_TERRAINSHADER_H
