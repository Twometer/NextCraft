//
// Created by twome on 22/01/2020.
//

#include "Section.h"

chunk::Section::Section() {
    this->data = new BlockData[16 * 16 * 16];
}

chunk::Section::~Section() {
    delete[] this->data;
}

chunk::BlockData *chunk::Section::GetBlockData(int x, int y, int z) {
    int idx = (y * 16 + z) * 16 + x;
    return data + idx;
}

void chunk::Section::SetBlockData(int x, int y, int z, chunk::BlockData block) {
    *GetBlockData(x, y, z) = block;
}

void chunk::Section::SetBlock(int x, int y, int z, uint8_t id) {
    GetBlockData(x, y, z)->id = id;
}

void chunk::Section::SetMeta(int x, int y, int z, uint8_t meta) {
    GetBlockData(x, y, z)->meta = meta;
}

