//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_VERTICES_H
#define NEXTCRAFT_VERTICES_H

#include <glad/glad.h>
#include <vector>

static const std::vector<GLfloat> NegXVertices = {
        0.0f, 0.0f, 0.0f, // Neg x
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, // Neg x
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f
};

static const std::vector<GLfloat> NegXTextures = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};

static const std::vector<GLfloat> NegYVertices = {
        1.0f, 0.0f, 1.0f, // Neg y
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, // Neg y
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
};

static const std::vector<GLfloat> NegYTextures = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
};

static const std::vector<GLfloat> NegZVertices = {
        1.0f, 1.0f, 0.0f, // Neg z
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  // Neg z
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
};

static const std::vector<GLfloat> NegZTextures = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
};

static const std::vector<GLfloat> PosXVertices = {
        1.0f, 0.0f, 0.0f, // Pos x
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, // Pos x
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
};

static const std::vector<GLfloat> PosXTextures = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
};

static const std::vector<GLfloat> PosYVertices = {
        1.0f, 1.0f, 1.0f, // Pos y
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, // Posy
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
};

static const std::vector<GLfloat> PosYTextures = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
};


static const std::vector<GLfloat> PosZVertices = {
        0.0f, 1.0f, 1.0f, // Pos z
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, // Pos z
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f
};

static const std::vector<GLfloat> PosZTextures = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f
};

static const std::vector<GLfloat> PlantVertices = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
};

static const std::vector<GLfloat> PlantTextures = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
};


static const std::vector<GLfloat> FlatVertices = {
        1.0f, 0.05f, 1.0f,
        1.0f, 0.05f, 0.0f,
        0.0f, 0.05f, 0.0f,
        1.0f, 0.05f, 1.0f,
        0.0f, 0.05f, 0.0f,
        0.0f, 0.05f, 1.0f
};

static const std::vector<GLfloat> FlatTextures = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
};

static const std::vector<GLfloat> FlatSideVertices = {
        0.05f, 0.0f, 0.05f, // Pos x
        0.05f, 1.0f, 0.95f,
        0.05f, 0.0f, 0.95f,
        0.05f, 1.0f, 0.95f, // Pos x
        0.05f, 0.0f, 0.05f,
        0.05f, 1.0f, 0.05f,
        0.05f, 0.0f, 0.05f, // Neg x
        0.05f, 0.0f, 0.95f,
        0.05f, 1.0f, 0.95f,
        0.05f, 0.0f, 0.05f, // Neg x
        0.05f, 1.0f, 0.95f,
        0.05f, 1.0f, 0.05f
};

static const std::vector<GLfloat> FlatSideTextures = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};

#endif //NEXTCRAFT_VERTICES_H
