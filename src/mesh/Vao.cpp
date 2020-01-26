//
// Created by twome on 26/01/2020.
//

#include "Vao.h"

Vao::Vao() {
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);

    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, nullptr);
}

Vao::~Vao() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &textureBuffer);

    glDeleteVertexArrays(1, &vaoId);
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
    glDrawArrays(GL_TRIANGLES, 0, triangles);
}
