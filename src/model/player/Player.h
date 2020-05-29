//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_PLAYER_H
#define NEXTCRAFT_PLAYER_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../world/AABB.h"
#include "GameMode.h"


#define GRAVITY 0.016f
#define SLIPPERINESS 0.75f
#define FLY_MOTION_MUL 0.85

struct Player {

    int entityId;

    GameMode gameMode;

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

    bool onGround = true;
    bool flying = false;

    void Move(glm::vec3 offset);

    void Update();

    void AddVelocity(glm::vec3 velocity);

    void Jump();

};

#endif //NEXTCRAFT_PLAYER_H
