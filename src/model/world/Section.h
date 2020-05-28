//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_SECTION_H
#define NEXTCRAFT_SECTION_H

#include <cstdint>
#include "BlockData.h"
#include "../../mesh/SectionMesh.h"

class SectionMesh;
namespace chunk {

    struct Section {
    public:
        int x;
        int y;
        int z;

        SectionMesh *mesh;

        BlockData *data;

        Section(int x, int y, int z);

        ~Section();

        BlockData &GetBlockData(int x, int y, int z);

        void SetBlockData(int x, int y, int z, BlockData block);

        void SetBlock(int x, int y, int z, uint8_t id);

        void SetMeta(int x, int y, int z, uint8_t meta);

    private:
        inline BlockData *GetBlockDataPtr(int x, int y, int z) const;

    };

}

#endif //NEXTCRAFT_SECTION_H
