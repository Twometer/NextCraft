//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_BLOCK_H
#define NEXTCRAFT_BLOCK_H

#include <cstdint>
#include "../../render/block/IBlockRenderer.h"

struct Sprite {
    int x;
    int y;
};

class IBlockRenderer;

struct Block {

    uint8_t id;

    bool noClip;

    bool noSelect;

    IBlockRenderer *blockRenderer;

    Block(uint8_t id, IBlockRenderer *blockRenderer) : id(id), noClip(false), noSelect(false),
                                                       blockRenderer(blockRenderer) {
    }

    Block *SetNoClip() {
        noClip = true;
        return this;
    }

    Block *SetNoSelect() {
        noSelect = true;
        return this;
    }

};

#endif //NEXTCRAFT_BLOCK_H
