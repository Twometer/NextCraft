//
// Created by twome on 28/05/2020.
//

#ifndef NEXTCRAFT_HIGHLIGHTSHADER_H
#define NEXTCRAFT_HIGHLIGHTSHADER_H

#include "IShader.h"

class HighlightShader : public IShader {
private:
    GLuint loc_viewMatrix;
    GLuint loc_projMatrix;
    GLuint loc_offset;
    GLuint loc_size;

public:
    HighlightShader() {
        Initialize("highlight");
    }

    void BindUniforms() override {
        loc_viewMatrix = GetLocation("viewMatrix");
        loc_projMatrix = GetLocation("projMatrix");
        loc_offset = GetLocation("offset");
        loc_size = GetLocation("size");
    }

    void SetOffset(const glm::vec3 &offset) const {
        LoadVec3(loc_offset, offset);
    }

    void SetSize(const glm::vec3 &size) const {
        LoadVec3(loc_size, size);
    }

    void SetViewMatrix(const glm::mat4 &matrix) const {
        LoadMatrix(loc_viewMatrix, matrix);
    }

    void SetProjectionMatrix(const glm::mat4 &matrix) const {
        LoadMatrix(loc_projMatrix, matrix);
    }


};

#endif //NEXTCRAFT_HIGHLIGHTSHADER_H

