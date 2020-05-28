//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_MESH_H
#define NEXTCRAFT_MESH_H


#include <vector>
#include <glad/glad.h>
#include "../util/FloatBuffer.h"

class Mesh {
private:
    FloatBuffer vertices;
    FloatBuffer colors;
    FloatBuffer texCoords;

public:
    explicit Mesh(int capacity);

    void AddVertex(GLfloat x, GLfloat y, GLfloat z);

    void AddColor(GLfloat r, GLfloat g, GLfloat b);

    void AddTexCoords(GLfloat u, GLfloat v);

    GLfloat *GetVertices();

    int GetVertexCount();

    GLfloat *GetColors();

    int GetColorCount();

    GLfloat *GetTexCoords();

    int GetTexCoordCount();

    void Clear();

};


#endif //NEXTCRAFT_MESH_H
