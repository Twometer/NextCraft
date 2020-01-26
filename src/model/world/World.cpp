//
// Created by twome on 22/01/2020.
//

#include "World.h"

void World::AddChunk(chunk::Chunk *chunk) {
    glm::ivec2 vec(chunk->x, chunk->z);
    chunks[vec] = chunk;
}

void World::RemoveChunk(int x, int z) {
    chunks.erase(glm::ivec2(x, z));
}

chunk::Chunk *World::GetChunk(int x, int z) {
    return chunks[glm::ivec2(x, z)];
}

chunk::BlockData &World::GetBlockData(int x, int y, int z) {
    return GetChunk(x >> 4, z >> 4)->GetBlockData(x & 15, y, z & 15);
}

void World::SetBlockData(int x, int y, int z, chunk::BlockData data) {
    GetChunk(x >> 4, z >> 4)->SetBlockData(x & 15, y, z & 15, data);
}

void World::SetBlock(int x, int y, int z, uint8_t id) {
    GetChunk(x >> 4, z >> 4)->SetBlock(x & 15, y, z & 15, id);
}

void World::SetMeta(int x, int y, int z, uint8_t meta) {
    GetChunk(x >> 4, z >> 4)->SetMeta(x & 15, y, z & 15, meta);
}
