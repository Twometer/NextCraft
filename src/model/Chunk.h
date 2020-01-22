//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_CHUNK_H
#define NEXTCRAFT_CHUNK_H

#include "../net/McBuffer.h"
#include "../net/ChunkMeta.h"

namespace chunk {

    class Chunk {
    public:
        int x;
        int z;

        static Chunk *Create(ChunkMeta &meta, McBuffer &buffer);

    };

}

#endif //NEXTCRAFT_CHUNK_H
