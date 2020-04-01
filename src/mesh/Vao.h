//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_VAO_H
#define NEXTCRAFT_VAO_H


#include <glad/glad.h>
#include "Mesh.h"

class Vao {
private:
    GLuint vaoId = 0;

    GLuint vertexBuffer = 0;
    GLuint colorBuffer = 0;
    GLuint textureBuffer = 0;

    int triangles = 0;

public:
    Vao();

    ~Vao();

    void Initialize();

    void SetData(Mesh &mesh);

    void Draw() const;

};


#endif //NEXTCRAFT_VAO_H
