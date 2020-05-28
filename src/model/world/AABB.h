//
// Created by twome on 28/05/2020.
//

#ifndef NEXTCRAFT_AABB_H
#define NEXTCRAFT_AABB_H


#include <glm/glm.hpp>

class AABB {
private:
    glm::vec3 p0;
    glm::vec3 p1;

public:
    AABB(glm::vec3 p0, glm::vec3 p1);

    AABB Expand(float x, float y, float z) const;

    float CollideX(AABB other, float xa) const;

    float CollideY(AABB other, float ya) const;

    float CollideZ(AABB other, float za) const;

    void Move(float x, float y, float z);

    glm::vec3 &GetCorner0();

    glm::vec3 &GetCorner1();
};


#endif //NEXTCRAFT_AABB_H
