//
// Created by twome on 22/01/2020.
//

#ifndef NEXTCRAFT_WORLD_H
#define NEXTCRAFT_WORLD_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "Chunk.h"
#include "BlockData.h"

class World {
private:
    std::unordered_map<glm::ivec2, chunk::Chunk *> chunks;

public:
    long worldAge;

    long time;

    void AddChunk(chunk::Chunk *chunk);

    void RemoveChunk(int x, int z);

    chunk::Chunk *GetChunk(int x, int z);

    chunk::BlockData &GetBlockData(int x, int y, int z);

    void SetBlockData(int x, int y, int z, chunk::BlockData data);

    void SetBlock(int x, int y, int z, uint8_t id);

    void SetMeta(int x, int y, int z, uint8_t meta);

};


#endif //NEXTCRAFT_WORLD_H
