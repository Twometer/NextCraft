//
// Created by twome on 27/05/2020.
//

#ifndef NEXTCRAFT_RAYCAST_H
#define NEXTCRAFT_RAYCAST_H


#include "RaycastResult.h"

class Raycast {
private:
    float range;
    float precision;

public:
    Raycast(float range, float precision);

    RaycastResult CastRay() const;
};


#endif //NEXTCRAFT_RAYCAST_H
