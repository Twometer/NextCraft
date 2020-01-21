//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_CHUNKUTILS_H
#define NEXTCRAFT_CHUNKUTILS_H

#include <cstdint>

struct ChunkData {
    int x;
    int z;
    uint16_t bitmask;
    int packetSize;
};

class ChunkUtils {
private:
    static unsigned int CountBits(uint16_t n) {
        unsigned int count = 0;
        while (n) {
            count += n & 1u;
            n >>= 1u;
        }
        return count;
    }

public:
    static int CalcPacketSize(uint16_t bitmask, bool skylight, bool continuous) {
        int length = CountBits(bitmask);
        int var3 = length * 2 * 16 * 16 * 16;
        int var4 = length * 16 * 16 * 16 / 2;
        int var5 = skylight ? length * 16 * 16 * 16 / 2 : 0;
        int var6 = continuous ? 256 : 0;
        return var3 + var4 + var5 + var6;
    }


};

#endif //NEXTCRAFT_CHUNKUTILS_H
