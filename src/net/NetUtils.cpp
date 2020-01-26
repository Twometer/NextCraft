#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-use-auto"
//
// Created by Twometer on 19/09/2019.
//

#include <cstring>
#include "NetUtils.h"

int NetUtils::GetVarIntSize(int val) {
    int size = 0;
    uint32_t uval = static_cast<uint32_t >(val);
    do {
        uval >>= 7u;
        size++;
    } while (uval != 0);
    return size;
}

int NetUtils::WriteVarInt(uint8_t *target, int val) {
    int allocated = 0;
    uint32_t uval = static_cast<uint32_t >(val);
    do {
        uint8_t byte = (uint8_t) (uval & 0b01111111u);
        uval >>= 7u;
        if (uval != 0) {
            byte |= 0b10000000u;
        }
        target[allocated++] = byte;
    } while (uval != 0);
    return allocated;
}

uint8_t *NetUtils::CreateVarInt(int val, int *len) {
    auto *c = new uint8_t[5];
    int allocated = WriteVarInt(c, val);
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

#pragma clang diagnostic pop