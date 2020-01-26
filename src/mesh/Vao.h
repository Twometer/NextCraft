//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_VAO_H
#define NEXTCRAFT_VAO_H


#include <glad/glad.h>
#include "Mesh.h"

class Vao {
private:
    GLuint vaoId;

    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint textureBuffer;

    int triangles;

public:
    explicit Vao();

    ~Vao();

    void SetData(Mesh &mesh);

    void Draw() const;

};


#endif //NEXTCRAFT_VAO_H
