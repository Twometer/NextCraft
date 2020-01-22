//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_SECTION_H
#define NEXTCRAFT_SECTION_H

#include <cstdint>

namespace chunk {

    struct BlockData {
        uint8_t id;
        uint8_t meta;
    };

    struct Section {
    public:
        BlockData *data;

        Section() {
            this->data = new BlockData[16 * 16 * 16];
        }

        ~Section() {
            delete[] data;
        }

        BlockData *GetBlockData(int x, int y, int z) {
            int idx = (y * 16 + z) * 16 + x;
            return data + idx;
        }

        void SetBlockData(int x, int y, int z, BlockData data) {
            *GetBlockData(x, y, z) = data;
        }

        void SetBlock(int x, int y, int z, uint8_t id) {
            GetBlockData(x, y, z)->id = id;
        }

    };

}

#endif //NEXTCRAFT_SECTION_H
