//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_MESH_H
#define NEXTCRAFT_MESH_H


#include <vector>
#include <glad/glad.h>

class Mesh {
private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> texCoords;

public:
    Mesh(int capacity);

    void AddVertex(GLfloat x, GLfloat y, GLfloat z);

    void AddColor(GLfloat r, GLfloat g, GLfloat b);

    void AddTexCoords(GLfloat u, GLfloat v);

    GLfloat *GetVertices();

    int GetVertexCount();

    GLfloat *GetColors();

    int GetColorCount();

    GLfloat *GetTexCoords();

    int GetTexCoordCount();

};


#endif //NEXTCRAFT_MESH_H
