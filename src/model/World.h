//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_WORLD_H
#define NEXTCRAFT_WORLD_H


#include "Chunk.h"
#include "BlockData.h"

class World {
public:
    long worldAge;

    long time;

    void AddChunk(chunk::Chunk *chunk);

    void RemoveChunk(int x, int z);

    chunk::Chunk *GetChunk(int x, int z);

    void SetBlockData(int x, int y, int z, chunk::BlockData data);

};


#endif //NEXTCRAFT_WORLD_H
