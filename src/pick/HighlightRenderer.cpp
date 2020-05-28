//
// Created by twome on 28/05/2020.
//

#include "HighlightRenderer.h"

const GLfloat HighlightRenderer::Vertices[] = {
        -0.001, 1.001, -0.001,
        -0.001, -0.001, -0.001,
        1.001, -0.001, -0.001,
        1.001, -0.001, -0.001,
        1.001, 1.001, -0.001,
        -0.001, 1.001, -0.001,
        -0.001, -0.001, 1.001,
        -0.001, -0.001, -0.001,
        -0.001, 1.001, -0.001,
        -0.001, 1.001, -0.001,
        -0.001, 1.001, 1.001,
        -0.001, -0.001, 1.001,
        1.001, -0.001, -0.001,
        1.001, -0.001, 1.001,
        1.001, 1.001, 1.001,
        1.001, 1.001, 1.001,
        1.001, 1.001, -0.001,
        1.001, -0.001, -0.001,
        -0.001, -0.001, 1.001,
        -0.001, 1.001, 1.001,
        1.001, 1.001, 1.001,
        1.001, 1.001, 1.001,
        1.001, -0.001, 1.001,
        -0.001, -0.001, 1.001,
        -0.001, 1.001, -0.001,
        1.001, 1.001, -0.001,
        1.001, 1.001, 1.001,
        1.001, 1.001, 1.001,
        -0.001, 1.001, 1.001,
        -0.001, 1.001, -0.001,
        -0.001, -0.001, -0.001,
        -0.001, -0.001, 1.001,
        1.001, -0.001, -0.001,
        1.001, -0.001, -0.001,
        -0.001, -0.001, 1.001,
        1.001, -0.001, 1.001
};

HighlightRenderer::HighlightRenderer() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 108, Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

HighlightRenderer::~HighlightRenderer() {
    glDeleteVertexArrays(1, &vao);
}

void HighlightRenderer::Render() const {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}


