//
// Created by twome on 21/01/2020.
//

#ifndef NEXTCRAFT_PLAYER_H
#define NEXTCRAFT_PLAYER_H

#include <string>

struct Player {

    std::string name;

    double posX;
    double posY;
    double posZ;

    float yaw;
    float pitch;

    float health;
    int hunger;

    float xpBar;
    int xpLevel;

};

#endif //NEXTCRAFT_PLAYER_H
