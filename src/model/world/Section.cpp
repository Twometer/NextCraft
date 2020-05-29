//
// Created by twome on 22/01/2020.
//

#include "Section.h"
#include "../block/BlockRegistry.h"

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
    CheckFluid(block.id);
}

void chunk::Section::SetBlock(int x, int y, int z, uint8_t id) {
    GetBlockDataPtr(x, y, z)->id = id;
    CheckFluid(id);
}

void chunk::Section::SetMeta(int x, int y, int z, uint8_t meta) {
    GetBlockDataPtr(x, y, z)->meta = meta;
}

chunk::BlockData *chunk::Section::GetBlockDataPtr(int x, int y, int z) const {
    int idx = (y * 16 + z) * 16 + x;
    return data + idx;
}

void chunk::Section::CheckFluid(uint8_t blockId) const {
    if (BlockRegistry::Get(blockId)->blockRenderer->RequiresFluidMesh()) {
        mesh->EnableFluidMesh();
    }
}

