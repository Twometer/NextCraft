//
// Created by twome on 27/05/2020.
//

#ifndef NEXTCRAFT_RAYCAST_H
#define NEXTCRAFT_RAYCAST_H


#include "RaycastResult.h"

class Raycast {
private:
    float precision;
    int raySteps;

public:
    Raycast(float range, float precision);

    RaycastResult CastRay() const;

private:
    BlockFace FindFace(glm::vec3 rayPos, int x, int y, int z) const;
};


#endif //NEXTCRAFT_RAYCAST_H
