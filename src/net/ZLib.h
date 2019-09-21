//
// Created by Twometer on 21/09/2019.
//

#ifndef NEXTCRAFT_ZLIB_H
#define NEXTCRAFT_ZLIB_H


#include <cstdint>

class ZLib {

public:
    static int Decompress(uint8_t *src, int srcLen, uint8_t *dst, int dstLen);

};


#endif //NEXTCRAFT_ZLIB_H
