//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_CHUNKMETA_H
#define NEXTCRAFT_CHUNKMETA_H

#include <cstdint>
#include "../McBuffer.h"

namespace chunk {

    struct ChunkMeta {
        int x;
        int z;
        bool continuous;
        uint16_t bitmask;
    };

    static ChunkMeta ReadChunkMeta(McBuffer &buffer, bool bulk) {
        int x = buffer.ReadInt();
        int z = buffer.ReadInt();
        bool continuous = bulk || buffer.ReadBool();
        uint16_t bitmask = buffer.ReadShort();
        return {x, z, continuous, bitmask};
    }

}

#endif //NEXTCRAFT_CHUNKMETA_H
