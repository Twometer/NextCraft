//
// Created by twome on 27/05/2020.
//

#ifndef NEXTCRAFT_RAYCASTRESULT_H
#define NEXTCRAFT_RAYCASTRESULT_H

#include <glm/vec3.hpp>
#include "../model/block/BlockFace.h"

struct RaycastResult {

    glm::vec3 blockPosition;

    BlockFace blockFace;

};

#endif //NEXTCRAFT_RAYCASTRESULT_H
