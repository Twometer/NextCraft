//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_PLAYER_H
#define NEXTCRAFT_PLAYER_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../world/AABB.h"


#define GRAVITY 0.016f
#define SLIPPERINESS 0.75f

struct Player {

    std::string name;

    double posX = 0.;
    double posY = 0.;
    double posZ = 0.;

    double motionX;
    double motionY;
    double motionZ;

    float yaw = 0.f;
    float pitch = 0.f;

    float health = 20.f;
    int hunger = 20;

    float xpBar = 0.f;
    int xpLevel = 0;

    bool onGround;

    void Move(glm::vec3 offset);

    void Update();

    void AddVelocity(glm::vec3 velocity);

    void Jump();

};

#endif //NEXTCRAFT_PLAYER_H
