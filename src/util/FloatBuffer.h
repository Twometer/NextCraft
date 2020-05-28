//
// Created by twome on 01/04/2020.
//

#ifndef NEXTCRAFT_FLOATBUFFER_H
#define NEXTCRAFT_FLOATBUFFER_H

#include <glad/glad.h>

/**
 * A dynamic GLfloat buffer
 */
class FloatBuffer {
private:
    int remaining = 0;
    int capacity = 0;

    GLfloat *data = nullptr;

public:
    explicit FloatBuffer(int capacity);

    ~FloatBuffer();

    void Add3d(GLfloat x, GLfloat y, GLfloat z);

    void Add2d(GLfloat x, GLfloat y);

    GLfloat *GetData();

    int GetSize();

    void Clear();

private:
    void Grow();
};


#endif //NEXTCRAFT_FLOATBUFFER_H
