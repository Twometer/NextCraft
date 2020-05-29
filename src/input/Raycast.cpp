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
    Player &player = NextCraft::GetPlayer();
    World &world = NextCraft::GetWorld();

    RaycastResult result{};

    float yaw = glm::radians(player.yaw);
    float pitch = glm::radians(player.pitch);

    glm::vec3 position = glm::vec3(player.posX, player.posY + 1.75, player.posZ);
    glm::vec3 direction = glm::vec3(
            glm::cos(pitch) * glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch) * glm::cos(yaw)
    ) * precision;

    for (int i = 0; i < raySteps; i++) {
        position += direction;

        int x = glm::floor(position.x);
        int y = glm::floor(position.y);
        int z = glm::floor(position.z);
        chunk::BlockData &block = world.GetBlockData(x, y, z);

        if (!BlockRegistry::Get(block.id)->noSelect) {
            result.blockPosition = glm::vec3(x, y, z);
            result.blockFace = FindFace(position, x, y, z);
            break;
        }
    }

    return result;
}

BlockFace Raycast::FindFace(glm::vec3 rayPos, int x, int y, int z) {
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
