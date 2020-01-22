//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_CHUNKMETA_H
#define NEXTCRAFT_CHUNKMETA_H

#include <cstdint>
#include "McBuffer.h"

namespace chunk {

    struct ChunkMeta {
        int x;
        int z;
        uint16_t bitmask;
    };

    ChunkMeta ReadChunkMeta(McBuffer &buffer) {
        int x = buffer.ReadInt();
        int z = buffer.ReadInt();
        uint16_t bitmask = buffer.ReadShort();
        return {x, z, bitmask};
    }

}

#endif //NEXTCRAFT_CHUNKMETA_H
