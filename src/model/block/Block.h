//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_BLOCK_H
#define NEXTCRAFT_BLOCK_H

#include <cstdint>
#include "../../render/block/IBlockRenderer.h"

struct Texture {
    int x;
    int y;
};

class IBlockRenderer;

struct Block {

    uint8_t id;

    IBlockRenderer *blockRenderer;

    Block(uint8_t id, IBlockRenderer *blockRenderer) : id(id), blockRenderer(blockRenderer) {
    }

};

#endif //NEXTCRAFT_BLOCK_H
