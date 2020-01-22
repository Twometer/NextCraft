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
                        uint8_t blockId = raw >> 4u;
                        uint8_t blockMeta = raw & 15u;
                        section->SetBlockData(x, y, z, {blockId, blockMeta});
                    }
                }
            }

            chunk->sections[j] = section;
        }
    }
    return chunk;
}

