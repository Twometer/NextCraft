//
// Created by twome on 28/05/2020.
//

#include <iostream>
#include "Player.h"
#include "../../NextCraft.h"

void Player::Move(glm::vec3 offset) {
    AABB playerBox = AABB(glm::vec3(posX - 0.33, posY, posZ - 0.33),
                          glm::vec3(posX + 0.33, posY + 1.9, posZ + 0.33));

    std::vector<AABB> collision = NextCraft::client->world.GetCubes(static_cast<int>(glm::floor(posX)),
                                                                    static_cast<int>(glm::floor(posY)),
                                                                    static_cast<int>(glm::floor(posZ)),
                                                                    4);

    double dx = offset.x;
    double dy = offset.y;
    double dz = offset.z;
    double xaOrg = offset.x;
    double yaOrg = offset.y;
    double zaOrg = offset.z;
    for (unsigned int i = 0; i < collision.size(); i++) {
        dy = static_cast<float>(collision.at(i).CollideY(playerBox, dy));
    }
    playerBox.Move(0, dy, 0);
    for (unsigned int i = 0; i < collision.size(); i++) {
        dx = static_cast<float>(collision.at(i).CollideX(playerBox, dx));
    }
    playerBox.Move(dx, 0, 0);
    for (unsigned int i = 0; i < collision.size(); i++) {
        dz = static_cast<float>(collision.at(i).CollideZ(playerBox, dz));
    }
    playerBox.Move(0, 0, dz);

    this->onGround = dy != yaOrg && yaOrg < 0.0;

    if (xaOrg != dx) motionX = 0.0f;
    if (yaOrg != dy) motionY = 0.0f;
    if (zaOrg != dz) motionZ = 0.0f;

    posX = (playerBox.GetCorner0().x + playerBox.GetCorner1().x) / 2;
    posY = playerBox.GetCorner0().y;
    posZ = (playerBox.GetCorner0().z + playerBox.GetCorner1().z) / 2;
}

void Player::Update() {
    Move(glm::vec3(motionX, motionY, motionZ));
    motionX *= SLIPPERINESS;
    motionY -= GRAVITY;
    motionZ *= SLIPPERINESS;

    // Avoid setbacks
    if (motionY < -2)
        motionY = -2;
}

void Player::AddVelocity(glm::vec3 velocity) {
    motionX += velocity.x;
    motionY += velocity.y;
    motionZ += velocity.z;
}

void Player::Jump() {
    if (onGround)
        motionY = 0.21;
}

