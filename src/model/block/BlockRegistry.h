//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_BLOCKREGISTRY_H
#define NEXTCRAFT_BLOCKREGISTRY_H

#include "Block.h"

class BlockRegistry {
private:
    static Block **blocks;

    static void Register(int id, Texture texture);

    static void Register(int id, Texture top, Texture side, Texture bottom);

    static void Register(int id, IBlockRenderer *blockRenderer);

public:
    static void Initialize();

    static Block *Get(int id);
};


#endif //NEXTCRAFT_BLOCKREGISTRY_H
