//
// Created by Twometer on 23 Jan 2020.
//

#ifndef NEXTCRAFT_BLOCKDATA_H
#define NEXTCRAFT_BLOCKDATA_H

#include <cstdint>

namespace chunk {

    struct BlockData {
        uint8_t id;
        uint8_t meta;

        explicit BlockData(uint16_t raw) {
            id = raw >> 4u;
            meta = raw & 15u;
        }
    };

}

#endif //NEXTCRAFT_BLOCKDATA_H
