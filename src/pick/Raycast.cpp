//
// Created by twome on 27/05/2020.
//

#include "Raycast.h"
#include "../model/player/Player.h"
#include "../NextCraft.h"

Raycast::Raycast(float range, float precision) : range(range), precision(precision) {
}

RaycastResult Raycast::CastRay() const {
    Player &player = NextCraft::client->player;
    World &world = NextCraft::client->world;

    glm::vec3 direction = glm::vec3(
            glm::cos(player.pitch) * glm::sin(player.yaw),
            glm::sin(player.pitch),
            glm::cos(player.pitch) * glm::cos(player.yaw)
    ) * precision;

    int raySteps = static_cast<int>(range / precision);

    glm::vec3 position = glm::vec3(player.posX, player.posY, player.posZ);

    for (int i = 0; i < raySteps; i++) {
        position += direction;

        int x = glm::floor(position.x);
        int y = glm::floor(position.y);
        int z = glm::floor(position.z);
        chunk::BlockData &block = world.GetBlockData(x, y, z);
    }
}
