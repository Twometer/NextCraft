//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_WORLD_H
#define NEXTCRAFT_WORLD_H


#include "Chunk.h"

class World {

public:
    void AddChunk(chunk::Chunk *chunk);

    void RemoveChunk(int x, int z);
};


#endif //NEXTCRAFT_WORLD_H
