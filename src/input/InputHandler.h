//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_INPUTHANDLER_H
#define NEXTCRAFT_INPUTHANDLER_H

#include "Raycast.h"

#define PHYSICS_DELAY 20

class InputHandler {
private:
    Raycast raycast = Raycast(4.2f, 0.005f);
    RaycastResult lookingAt{};

    bool spacebarHeld;
    double prevSpacebarHit;

    int physicsWaitTicks;

public:
    void HandleInput();

    const RaycastResult &GetLookingAt() const;

};


#endif //NEXTCRAFT_INPUTHANDLER_H
