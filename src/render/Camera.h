//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_CAMERA_H
#define NEXTCRAFT_CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

public:
    glm::mat4 CalculateMatrix();

    glm::mat4 GetViewMatrix();

    glm::mat4 GetProjectionMatrix();

};


#endif //NEXTCRAFT_CAMERA_H
