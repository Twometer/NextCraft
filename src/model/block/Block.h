//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_BLOCK_H
#define NEXTCRAFT_BLOCK_H

#include <cstdint>

struct Texture {
    int x;
    int y;
};

struct Block {

    uint8_t id;

    Texture topTex;
    Texture sideTex;
    Texture bottomTex;

    Block(uint8_t id, Texture top, Texture side, Texture bottom) {
        this->id = id;
        this->topTex = top;
        this->sideTex = side;
        this->bottomTex = bottom;
    }

};

#endif //NEXTCRAFT_BLOCK_H
