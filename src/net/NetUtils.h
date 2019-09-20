//
// Created by Twometer on 19/09/2019.
//

#ifndef NEXTCRAFT_NETUTILS_H
#define NEXTCRAFT_NETUTILS_H


#include <cstdint>

class NetUtils {
public:
    static int GetVarIntSize(int val);

    static int WriteVarInt(uint8_t *target, int val);

    static uint8_t *CreateVarInt(int val, int *len);

    static int CountBits(uint32_t n);

};


#endif //NEXTCRAFT_NETUTILS_H
