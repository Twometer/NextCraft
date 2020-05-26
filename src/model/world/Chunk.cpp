//
// Created by twome on 22/01/2020.
//

#include <cstring>
#include "Chunk.h"

using namespace chunk;

Chunk::Chunk(int x, int z) {
    this->x = x;
    this->z = z;
    this->sections = new Section *[16];

    for (int i = 0; i < 16; i++) sections[i] = nullptr;
}

Chunk *Chunk::Create(ChunkMeta &meta, McBuffer &buffer, int &filledSections) {
    auto *chunk = new Chunk(meta.x, meta.z);
    for (unsigned int j = 0; j < 16; j++) { // Iterate sections
        if ((meta.bitmask & (1u << j)) != 0) { // Check if section is present
            auto *section = new Section(meta.x, j, meta.z);

            // Read section
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    for (int x = 0; x < 16; x++) {
                        uint16_t raw = buffer.ReadBlockData();
                        section->SetBlockData(x, y, z, BlockData(raw));
                    }
                }
            }

            chunk->sections[j] = section;
            filledSections++;
        }
    }
    return chunk;
}

BlockData &Chunk::GetBlockData(int x, int y, int z) {
    Section *section = GetSection(y >> 4);
    if (section == nullptr)
        return BlockData::null;
    return section->GetBlockData(x, y & 15, z);
}

void Chunk::SetBlockData(int x, int y, int z, BlockData data) {
    EnsureSectionExists(y);
    sections[y >> 4]->SetBlockData(x, y & 15, z, data);
}

void Chunk::SetBlock(int x, int y, int z, uint8_t id) {
    EnsureSectionExists(y);
    sections[y >> 4]->SetBlock(x, y & 15, z, id);
}

void Chunk::SetMeta(int x, int y, int z, uint8_t meta) {
    EnsureSectionExists(y);
    sections[y >> 4]->SetMeta(x, y & 15, z, meta);
}

void Chunk::EnsureSectionExists(int y) {
    int yIdx = y >> 4;
    if (sections[yIdx] == nullptr)
        sections[yIdx] = new Section(x, yIdx, z);
}

Chunk::~Chunk() {
    for (int i = 0; i < 16; i++)
        delete sections[i];
    delete[] sections;
}

