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

    memset(this->sections, 0, sizeof(Section *) * 16);
}

Chunk *Chunk::Create(ChunkMeta &meta, McBuffer &buffer) {
    auto *chunk = new Chunk(meta.x, meta.z);
    for (unsigned int j = 0; j < 16; j++) { // Iterate sections
        if ((meta.bitmask & (1u << j)) != 0) { // Check if section is present
            auto *section = new Section();

            // Read section
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    for (int x = 0; x < 16; x++) {
                        uint16_t raw = buffer.ReadShort();
                        section->SetBlockData(x, y, z, BlockData(raw));
                    }
                }
            }

            chunk->sections[j] = section;
        }
    }
    return chunk;
}

BlockData &Chunk::GetBlockData(int x, int y, int z) {
    return sections[y >> 4]->GetBlockData(x, y, z);
}

void Chunk::SetBlockData(int x, int y, int z, BlockData data) {
    sections[y >> 4]->SetBlockData(x, y, z, data);
}

void Chunk::SetBlock(int x, int y, int z, uint8_t id) {
    sections[y >> 4]->SetBlock(x, y, z, id);
}

void Chunk::SetMeta(int x, int y, int z, uint8_t meta) {
    sections[y >> 4]->SetMeta(x, y, z, meta);
}

