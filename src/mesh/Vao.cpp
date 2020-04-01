//
// Created by twome on 26/01/2020.
//

#include "Vao.h"
#include "../util/Logger.h"

Vao::Vao() {
}

Vao::~Vao() {
    glDeleteBuffers(1, &vertexBuffer);
    GL_LOG()
    glDeleteBuffers(1, &colorBuffer);
    GL_LOG()
    glDeleteBuffers(1, &textureBuffer);
    GL_LOG()

    glDeleteVertexArrays(1, &vaoId);
    GL_LOG()
}

void Vao::SetData(Mesh &mesh) {
    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetVertexCount() * sizeof(GLfloat), mesh.GetVertices(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetColorCount() * sizeof(GLfloat), mesh.GetColors(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetTexCoordCount() * sizeof(GLfloat), mesh.GetTexCoords(), GL_DYNAMIC_DRAW);

    this->triangles = mesh.GetVertexCount() / 3;
}

void Vao::Draw() const {
    glBindVertexArray(vaoId);
    GL_LOG()

    glDrawArrays(GL_TRIANGLES, 0, triangles);
    GL_LOG()
}

void Vao::Initialize() {
    if (vaoId != 0)
        return;

    glGenVertexArrays(1, &vaoId);
    GL_LOG()

    glBindVertexArray(vaoId);
    GL_LOG()

    glEnableVertexAttribArray(0);
    GL_LOG()
    glEnableVertexAttribArray(1);
    GL_LOG()
    glEnableVertexAttribArray(2);
    GL_LOG()

    glGenBuffers(1, &vertexBuffer);
    GL_LOG()
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    GL_LOG()
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    GL_LOG()

    glGenBuffers(1, &colorBuffer);
    GL_LOG()
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    GL_LOG()
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);
    GL_LOG()

    glGenBuffers(1, &textureBuffer);
    GL_LOG()
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    GL_LOG()
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, nullptr);
    GL_LOG()
}
