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
    Register(2, {8, 5}, {5, 5}, {30, 1});            // Grass
    Register(3, {30, 1});                                                   // Dirt
    Register(4, {3, 1});
    Register(5, {29, 7});
    Register(7, {5, 0});
    Register(8, {2, 12});
    Register(9, {26, 10});
    Register(10, {0, 12});
    Register(11, {0, 12});
    Register(12, {16, 9});
    Register(13, {9, 5});
    Register(17, {29, 6}, {28, 6}, {29, 6});
    Register(18, {13, 6});

    Register(255, {23, 10});                                                // Missing Texture
}

Block *BlockRegistry::Get(int id) {
    Block *block = blocks[id];
    return block == nullptr ? blocks[255] : block;
}


