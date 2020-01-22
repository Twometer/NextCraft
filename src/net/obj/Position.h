//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_POSITION_H
#define NEXTCRAFT_POSITION_H

#include <cstdint>

struct Position {

    int x;
    int y;
    int z;

    Position(uint64_t pos) {
        this->x = (int) (pos >> 38u);
        this->y = (int) (pos << 26u >> 52u);
        this->z = (int) (pos << 38u >> 38u);
        if (x >= 33554432) { x -= 67108864; }
        if (y >= 2048) { y -= 4096; }
        if (z >= 33554432) { z -= 67108864; }
    }

    uint64_t Serialize() {
        return (((uint64_t) x & 0x3FFFFFFu) << 38u)
               | (((uint64_t) y & 0xFFFu) << 26u)
               | ((uint64_t) z & 0x3FFFFFFu);
    }

};

#endif //NEXTCRAFT_POSITION_H
