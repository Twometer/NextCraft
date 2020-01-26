//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_PLAYER_H
#define NEXTCRAFT_PLAYER_H

#include <glm/glm.hpp>
#include <string>

struct Player {

    std::string name;

    double posX = 0.;
    double posY = 0.;
    double posZ = 0.;

    float yaw = 0.f;
    float pitch = 0.f;

    float health = 20.f;
    int hunger = 20;

    float xpBar = 0.f;
    int xpLevel = 0;

    void Move(glm::vec3 offset) {
        posX += offset.x;
        posY += offset.y;
        posZ += offset.z;
    }

};

#endif //NEXTCRAFT_PLAYER_H
