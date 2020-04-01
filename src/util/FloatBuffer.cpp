//
// Created by twome on 01/04/2020.
//

#include <cstring>
#include "FloatBuffer.h"

FloatBuffer::FloatBuffer(int capacity) {
    this->capacity = capacity;
    this->remaining = capacity;
    this->data = new GLfloat[capacity];
    memset(data, 0, sizeof(GLfloat) * capacity);
}

FloatBuffer::~FloatBuffer() {
    delete[] data;
}

void FloatBuffer::Add3d(GLfloat x, GLfloat y, GLfloat z) {
    if (remaining < 3) Grow();
    int offset = capacity - remaining;
    data[offset] = x;
    data[offset + 1] = y;
    data[offset + 2] = z;
    remaining -= 3;
}

void FloatBuffer::Add2d(GLfloat x, GLfloat y) {
    if (remaining < 2) Grow();
    int offset = capacity - remaining;
    data[offset] = x;
    data[offset + 1] = y;
    remaining -= 2;
}

void FloatBuffer::Grow() {
    int newCapacity = capacity * 1.5;

    auto *newData = new GLfloat[newCapacity];
    memset(newData, 0, sizeof(GLfloat) * newCapacity);

    int curCount = capacity - remaining;
    memcpy(newData, data, curCount);

    this->capacity = newCapacity;
    this->remaining = newCapacity - curCount;

    float *oldData = data;
    this->data = newData;
    delete[] oldData;
}

GLfloat *FloatBuffer::GetData() {
    return data;
}

int FloatBuffer::GetSize() {
    return capacity - remaining;
}
