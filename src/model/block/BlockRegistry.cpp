//
// Created by twome on 26/01/2020.
//

#include <cstring>
#include "BlockRegistry.h"

Block **BlockRegistry::blocks;

void BlockRegistry::Register(int id, Texture texture) {
    blocks[id] = new Block(id, texture, texture, texture);
}

void BlockRegistry::Register(int id, Texture top, Texture side, Texture bottom) {
    blocks[id] = new Block(id, top, side, bottom);
}

void BlockRegistry::Initialize() {
    blocks = new Block *[256];
    memset(blocks, 0, 256 * sizeof(Block *));


    Register(0, {0, 0});                                                     // Air
    Register(1, {2, 10});                                                   // Stone
    Register(2, {8, 5}, {5, 5}, {30, 1});         // Grass
    Register(3, {30, 1});                                                   // Dirt

    Register(255, {23, 10});                                                // Missing Texture
}

Block *BlockRegistry::Get(int id) {
    Block *block = blocks[id];
    return block == nullptr ? blocks[255] : block;
}


