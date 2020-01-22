//
// Created by twome on 22/01/2020.
//

#include "Chunk.h"

using namespace chunk;

Chunk *Chunk::Create(ChunkMeta &meta, McBuffer &buffer) {
    auto *chunk = new Chunk();
    chunk->x = meta.x;
    chunk->z = meta.z;

    for (unsigned int j = 0; j < 16; j++) { // Iterate sections
        if ((meta.bitmask & (1u << j)) != 0) { // Check if section is present

            // Read section
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    for (int x = 0; x < 16; x++) {
                        uint16_t raw = buffer.ReadShort();
                        uint8_t blockId = raw >> 4u;
                        uint8_t meta = raw & 15u;

                    }
                }
            }

        }
    }
    return chunk;
}

