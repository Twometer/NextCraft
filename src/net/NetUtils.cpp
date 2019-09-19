//
// Created by Twometer on 19/09/2019.
//

#include <cstring>
#include "NetUtils.h"

uint8_t *NetUtils::CreateVarInt(int val, int *len) {
    auto *c = new uint8_t[5];
    int allocated = 0;
    do {
        uint8_t byte = (char) (val & 0b01111111);
        val = ((unsigned int) val) >> 7;
        if (val != 0) {
            byte |= 0b10000000;
        }
        c[allocated++] = byte;
    } while (val != 0);

    *len = allocated;

    return c;
}

int NetUtils::CountBits(uint32_t n) {
    uint32_t count = 0;
    while (n) {
        count += n & 1u;
        n >>= 1u;
    }
    return count;
}
