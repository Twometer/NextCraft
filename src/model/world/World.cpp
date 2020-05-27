//
// Created by twome on 22/01/2020.
//

#include "World.h"

void World::AddChunk(chunk::Chunk *chunk) {
    auto vec = GetKey(chunk->x, chunk->z);
    chunks[vec] = chunk;
}

void World::RemoveChunk(int x, int z) {
    chunk::Chunk *removed = GetChunk(x, z);
    chunks.erase(GetKey(x, z));
    staleChunks.push_back(removed);
}

chunk::Chunk *World::GetChunk(int x, int z) {
    auto vec = GetKey(x, z);
    if (chunks.find(vec) == chunks.end())
        return nullptr;
    return chunks[vec];
}

chunk::BlockData &World::GetBlockData(int x, int y, int z) {
    chunk::Chunk *chunk = GetChunk(x >> 4, z >> 4);
    if (chunk == nullptr)
        return chunk::BlockData::null;
    return chunk->GetBlockData(x & 15, y, z & 15);
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

std::map<uint64_t, chunk::Chunk *> World::GetChunks() {
    return chunks;
}

void World::Cleanup() {
    if (staleChunks.empty())
        return;

    for (chunk::Chunk *chk :staleChunks)
        delete chk;
    staleChunks.clear();
}

uint64_t World::GetKey(int x, int z) {
    auto ux = (uint64_t) ((uint32_t) x);
    auto uz = (uint64_t) ((uint32_t) z);
    return (ux << 32ul) | uz;
}
