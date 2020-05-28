//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_TERRAINSHADER_H
#define NEXTCRAFT_TERRAINSHADER_H

#include "IShader.h"

class TerrainShader : public IShader {
private:
    GLuint loc_viewMatrix;
    GLuint loc_projMatrix;
    GLuint loc_skyColor;
    GLuint loc_texture;
    GLuint loc_opacity;

public:
    TerrainShader() {
        Initialize("terrain");
    }

    void BindUniforms() override {
        loc_viewMatrix = GetLocation("viewMatrix");
        loc_projMatrix = GetLocation("projMatrix");
        loc_skyColor = GetLocation("skyColor");
        loc_opacity = GetLocation("opacity");
        loc_texture = GetLocation("tex");
    }

    void SetOpacity(float opacity) const {
        glUniform1f(loc_opacity, opacity);
    }

    void SetViewMatrix(const glm::mat4 &matrix) const {
        LoadMatrix(loc_viewMatrix, matrix);
    }

    void SetProjectionMatrix(const glm::mat4 &matrix) const {
        LoadMatrix(loc_projMatrix, matrix);
    }

    void SetSkyColor(const glm::vec3 &skyColor) const {
        LoadVec3(loc_skyColor, skyColor);
    }

    void SetTextureUnit(const int idx) const {
        glUniform1i(loc_texture, idx);
    }

};

#endif //NEXTCRAFT_TERRAINSHADER_H

