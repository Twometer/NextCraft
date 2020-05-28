//
// Created by twome on 28/05/2020.
//

#include "AABB.h"

AABB::AABB(glm::vec3 p0, glm::vec3 p1) : p0(p0), p1(p1) {

}

AABB AABB::Expand(float x, float y, float z) const {
    glm::vec3 p0_ = p0;
    glm::vec3 p1_ = p1;
    if (x < 0) p0_.x += x;
    if (x > 0) p1_.x += x;
    if (y < 0) p0_.y += y;
    if (y > 0) p1_.y += y;
    if (z < 0) p0_.z += z;
    if (z > 0) p1_.z += z;
    return {p0_, p1_};
}

void AABB::Move(float x, float y, float z) {
    glm::vec3 offset = glm::vec3(x, y, z);
    p0 += offset;
    p1 += offset;
}

float AABB::CollideX(AABB other, float xa) const {
    if (other.p1.y <= p0.y || other.p0.y >= p1.y) return xa;
    if (other.p1.z <= p0.z || other.p0.z >= p1.z) return xa;
    if (xa > 0 && other.p1.x <= p0.x) {
        float max = p0.x - other.p1.x;
        if (max < xa) xa = max;
    }
    if (xa < 0 && other.p0.x >= p1.x) {
        float max = p1.x - other.p0.x;
        if (max > xa) xa = max;
    }
    return xa;
}

float AABB::CollideY(AABB other, float ya) const {
    if (other.p1.x <= p0.x || other.p0.x >= p1.x) return ya;
    if (other.p1.z <= p0.z || other.p0.z >= p1.z) return ya;
    if (ya > 0 && other.p1.y <= p0.y) {
        float max = p0.y - other.p1.y;
        if (max < ya) ya = max;
    }
    if (ya < 0 && other.p0.y >= p1.y) {
        float max = p1.y - other.p0.y;
        if (max > ya) ya = max;
    }
    return ya;
}

float AABB::CollideZ(AABB other, float za) const {
    if (other.p1.x <= p0.x || other.p0.x >= p1.x) return za;
    if (other.p1.y <= p0.y || other.p0.y >= p1.y) return za;
    if (za > 0 && other.p1.z <= p0.z) {
        float max = p0.z - other.p1.z;
        if (max < za) za = max;
    }
    if (za < 0 && other.p0.z >= p1.z) {
        float max = p1.z - other.p0.z;
        if (max > za) za = max;
    }
    return za;
}

glm::vec3 &AABB::GetCorner0() {
    return p0;
}

glm::vec3 &AABB::GetCorner1() {
    return p1;
}

