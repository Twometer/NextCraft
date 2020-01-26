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

    Register(0, {23, 10});
    Register(1, {2, 10});
    Register(2, {8, 5}, {5, 5}, {30, 1});
    Register(3, {30, 1});
}

Block *BlockRegistry::Get(int id) {
    Block *block = blocks[id];
    return block == nullptr ? blocks[0] : block;
}


