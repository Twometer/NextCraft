//
// Created by twome on 26/01/2020.
//

#include "Mesh.h"

Mesh::Mesh(int capacity)
        : vertices(capacity),
          colors(capacity),
          texCoords(capacity / 3 * 2) {
}

void Mesh::AddVertex(GLfloat x, GLfloat y, GLfloat z) {
    vertices.Add3d(x, y, z);
}

void Mesh::AddColor(GLfloat r, GLfloat g, GLfloat b) {
    colors.Add3d(r, g, b);
}

void Mesh::AddTexCoords(GLfloat u, GLfloat v) {
    texCoords.Add2d(u, v);
}

GLfloat *Mesh::GetVertices() {
    return vertices.GetData();
}

int Mesh::GetVertexCount() {
    return vertices.GetSize();
}

GLfloat *Mesh::GetColors() {
    return colors.GetData();
}

int Mesh::GetColorCount() {
    return colors.GetSize();
}

GLfloat *Mesh::GetTexCoords() {
    return texCoords.GetData();
}

int Mesh::GetTexCoordCount() {
    return texCoords.GetSize();
}
