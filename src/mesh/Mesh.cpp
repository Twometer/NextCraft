//
// Created by twome on 26/01/2020.
//

#include "Mesh.h"

Mesh::Mesh(int capacity) {
    vertices = std::vector<GLfloat>();
    colors = std::vector<GLfloat>();
    texCoords = std::vector<GLfloat>();

    vertices.reserve(capacity);
    colors.reserve(capacity);
    texCoords.reserve(capacity / 3 * 2);
}

void Mesh::AddVertex(GLfloat x, GLfloat y, GLfloat z) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void Mesh::AddColor(GLfloat r, GLfloat g, GLfloat b) {
    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);
}

void Mesh::AddTexCoords(GLfloat u, GLfloat v) {
    texCoords.push_back(u);
    texCoords.push_back(v);
}

GLfloat *Mesh::GetVertices() {
    return vertices.data();
}

int Mesh::GetVertexCount() {
    return vertices.size();
}

GLfloat *Mesh::GetColors() {
    return colors.data();
}

int Mesh::GetColorCount() {
    return colors.size();
}

GLfloat *Mesh::GetTexCoords() {
    return texCoords.data();
}

int Mesh::GetTexCoordCount() {
    return texCoords.size();
}
