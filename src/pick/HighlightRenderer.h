//
// Created by twome on 28/05/2020.
//

#ifndef NEXTCRAFT_HIGHLIGHTRENDERER_H
#define NEXTCRAFT_HIGHLIGHTRENDERER_H


#include <glad/glad.h>

class HighlightRenderer {
private:
    static const GLfloat Vertices[];

    GLuint vao;

public:
    HighlightRenderer();

    ~HighlightRenderer();

    void Render() const;
};


#endif //NEXTCRAFT_HIGHLIGHTRENDERER_H
