//
// Created by twome on 27/05/2020.
//

#include "Raycast.h"
#include "../model/player/Player.h"
#include "../NextCraft.h"

Raycast::Raycast(float range, float precision) : precision(precision),
                                                 raySteps(static_cast<int>(range / precision)) {
}

RaycastResult Raycast::CastRay() const {
    Player &player = NextCraft::client->player;
    World &world = NextCraft::client->world;

    RaycastResult result{};

    glm::vec3 position = glm::vec3(player.posX, player.posY, player.posZ);
    glm::vec3 direction = glm::vec3(
            glm::cos(player.pitch) * glm::sin(player.yaw),
            glm::sin(player.pitch),
            glm::cos(player.pitch) * glm::cos(player.yaw)
    ) * precision;

    for (int i = 0; i < raySteps; i++) {
        position += direction;

        int x = glm::floor(position.x);
        int y = glm::floor(position.y);
        int z = glm::floor(position.z);
        chunk::BlockData &block = world.GetBlockData(x, y, z);

        if (block.id != 0) {
            result.blockPosition = glm::vec3(x, y, z);
            result.blockFace = FindFace(position, x, y, z);
        }
    }

    return result;
}

BlockFace Raycast::FindFace(glm::vec3 rayPos, int x, int y, int z) const {
    float xd = glm::round(rayPos.x - x);
    float yd = glm::round(rayPos.y - y);
    float zd = glm::round(rayPos.z - z);

    if (xd == 1) return PosX;
    else if (xd == -1) return NegX;
    else if (yd == 1) return PosY;
    else if (yd == -1) return NegY;
    else if (zd == 1) return PosZ;
    else if (zd == -1) return NegZ;
    return None;
}