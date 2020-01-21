//
// Created by Twometer on 21/09/2019.
//

#include <zlib.h>
#include "ZLib.h"

int ZLib::Decompress(uint8_t *src, int srcLen, uint8_t *dst, int dstLen) {
    z_stream zInfo = {nullptr};
    zInfo.total_in = zInfo.avail_in = srcLen;
    zInfo.total_out = zInfo.avail_out = dstLen;
    zInfo.next_in = src;
    zInfo.next_out = dst;

    int nErr, nRet = -1;
    nErr = inflateInit(&zInfo);
    if (nErr == Z_OK) {
        nErr = inflate(&zInfo, Z_FINISH);
        if (nErr == Z_STREAM_END) {
            nRet = zInfo.total_out;
        }
    }
    inflateEnd(&zInfo);
    return nRet;
}
