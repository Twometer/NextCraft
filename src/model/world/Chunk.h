//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_CHUNK_H
#define NEXTCRAFT_CHUNK_H

#include "../../net/McBuffer.h"
#include "../../net/obj/ChunkMeta.h"
#include "Section.h"

namespace chunk {

    class Chunk {
    private:
        Section **sections;

        Chunk(int x, int z);

        void EnsureSectionExists(int y);

    public:
        int x;
        int z;

        ~Chunk();

        static Chunk *Create(ChunkMeta &meta, McBuffer &buffer, int &filledSections);

        BlockData &GetBlockData(int x, int y, int z);

        void SetBlockData(int x, int y, int z, BlockData data);

        void SetBlock(int x, int y, int z, uint8_t id);

        void SetMeta(int x, int y, int z, uint8_t meta);

        inline Section *GetSection(int idx) {
            if (idx < 0 || idx > 15)
                return nullptr;
            return sections[idx];
        }
    };

}

#endif //NEXTCRAFT_CHUNK_H
