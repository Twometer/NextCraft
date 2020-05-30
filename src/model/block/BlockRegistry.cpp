//
// Created by twome on 26/01/2020.
//

#include <cstring>
#include "BlockRegistry.h"
#include "../../render/block/DefaultBlockRenderer.h"
#include "../../render/block/PlantRenderer.h"
#include "../../render/block/LeavesRenderer.h"
#include "../../render/block/FluidRenderer.h"

Block **BlockRegistry::blocks;

Block *BlockRegistry::Register(int id, Sprite texture) {
    return blocks[id] = new Block(id, new DefaultBlockRenderer(texture, texture, texture));
}

Block *BlockRegistry::Register(int id, Sprite top, Sprite side, Sprite bottom) {
    return blocks[id] = new Block(id, new DefaultBlockRenderer(top, side, bottom));
}

Block *BlockRegistry::Register(int id, IBlockRenderer *blockRenderer) {
    return blocks[id] = new Block(id, blockRenderer);
}

void BlockRegistry::Initialize() {
    blocks = new Block *[256];
    memset(blocks, 0, 256 * sizeof(Block *));


    Register(0, {0, 0})->SetNoClip()->SetNoSelect(); // Air
    Register(1, {2, 10}); // Stone
    Register(2, {8, 5}, {5, 5}, {30, 1}); // Grass
    Register(3, {30, 1});  // Dirt
    Register(4, {3, 1});   // Cobblestone
    Register(5, {29, 7});  // Wooden Planks
    Register(7, {5, 0});   // Bedrock
    Register(8, new FluidRenderer({2, 12}))->SetNoClip()->SetNoSelect();  // Flowing Water
    Register(9, new FluidRenderer({26, 10}))->SetNoClip()->SetNoSelect(); // Still Water
    Register(10, new FluidRenderer({0, 12}))->SetNoClip()->SetNoSelect(); // Flowing Lava
    Register(11, new FluidRenderer({0, 12}))->SetNoClip()->SetNoSelect(); // Still Lava
    Register(12, {16, 9}); // Sand
    Register(13, {9, 5});  // Gravel
    Register(14, {4, 5});  // Gold Ore
    Register(15, {4, 6});  // Iron Ore
    Register(16, {1, 1});  // Coal Ore
    Register(17, {29, 6}, {28, 6}, {29, 6}); // Log
    Register(18, new LeavesRenderer({13, 6})); // Leaves
    Register(19, {0, 10}); // Sponge
    Register(20, {0, 4});  // Glass
    Register(21, {11, 6}); // Lapis Lazuli Ore
    Register(22, {10, 6}); // Lapis Lazuli Block
    Register(24, {21, 9}, {19, 9}, {17, 9}); // Sandstone
    Register(25, {7, 6});  // Note block
    Register(31, new PlantRenderer({15, 10}))->SetNoClip();  // Tall grass
    Register(35, {18, 11}); // Wool
    Register(45, {15, 0}); // Bricks
    Register(46, {18, 10}, {17, 10}, {16, 10}); // TNT
    Register(47, {29, 7}, {12, 0}, {29, 7}); // Bookshelf
    Register(48, {4, 1}); // Mossy Stone
    Register(49, {5, 3}); // Obsidian
    Register(52, {4, 7}); // Spawner
    Register(56, {29, 1}); // Diamond ore
    Register(47, {13, 1}, {11, 1}, {29, 7}); // Crafting Table

    Register(255, {23, 10}); // Unknown block
}

Block *BlockRegistry::Get(int id) {
    Block *block = blocks[id];
    return block == nullptr ? blocks[255] : block;
}


