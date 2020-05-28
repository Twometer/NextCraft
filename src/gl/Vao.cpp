//
// Created by twome on 26/01/2020.
//

#include "Vao.h"
#include "../util/Logger.h"

Vao::Vao() {
}

Vao::~Vao() {
    glDeleteBuffers(1, &vertexBuffer);
    glCheckErrors()
    glDeleteBuffers(1, &colorBuffer);
    glCheckErrors()
    glDeleteBuffers(1, &textureBuffer);
    glCheckErrors()

    glDeleteVertexArrays(1, &vaoId);
    glCheckErrors()
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
    glCheckErrors()

    glDrawArrays(GL_TRIANGLES, 0, triangles);
    glCheckErrors()
}

void Vao::Initialize() {
    if (vaoId != 0)
        return;

    glGenVertexArrays(1, &vaoId);
    glCheckErrors()

    glBindVertexArray(vaoId);
    glCheckErrors()

    glEnableVertexAttribArray(0);
    glCheckErrors()
    glEnableVertexAttribArray(1);
    glCheckErrors()
    glEnableVertexAttribArray(2);
    glCheckErrors()

    glGenBuffers(1, &vertexBuffer);
    glCheckErrors()
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glCheckErrors()
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    glCheckErrors()

    glGenBuffers(1, &colorBuffer);
    glCheckErrors()
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glCheckErrors()
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);
    glCheckErrors()

    glGenBuffers(1, &textureBuffer);
    glCheckErrors()
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glCheckErrors()
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, nullptr);
    glCheckErrors()
}
