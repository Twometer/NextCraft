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

chunk::BlockData &chunk::Section::GetBlockData(int x, int y, int z) {
    return *GetBlockDataPtr(x, y, z);
}

void chunk::Section::SetBlockData(int x, int y, int z, chunk::BlockData block) {
    *GetBlockDataPtr(x, y, z) = block;
}

void chunk::Section::SetBlock(int x, int y, int z, uint8_t id) {
    GetBlockDataPtr(x, y, z)->id = id;
}

void chunk::Section::SetMeta(int x, int y, int z, uint8_t meta) {
    GetBlockDataPtr(x, y, z)->meta = meta;
}

chunk::BlockData *chunk::Section::GetBlockDataPtr(int x, int y, int z) {
    int idx = (y * 16 + z) * 16 + x;
    return data + idx;
}

