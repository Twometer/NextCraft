//
// Created by twome on 22/01/2020.
//

#include "Section.h"

chunk::Section::Section(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->data = new BlockData[16 * 16 * 16];
    this->mesh = new SectionMesh(this);
}

chunk::Section::~Section() {
    delete[] data;
    delete mesh;
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

chunk::BlockData *chunk::Section::GetBlockDataPtr(int x, int y, int z) const {
    int idx = (y * 16 + z) * 16 + x;
    return data + idx;
}

