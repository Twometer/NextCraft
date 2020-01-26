//
// Created by twome on 26/01/2020.
//

#include "Camera.h"
#include "../NextCraft.h"

#define PI 3.141592653589793f

glm::mat4 Camera::CalculateMatrix() {
    Viewport &viewport = NextCraft::viewport;
    Player &player = NextCraft::client->player;

    glm::vec3 eyePosition = glm::vec3(player.posX, player.posY + 1.75, player.posZ);
    float yaw = glm::radians(player.yaw);
    float pitch = glm::radians(player.pitch);

    glm::vec3 direction(
            glm::cos(pitch) * glm::sin(yaw),
            glm::sin(pitch),
            glm::cos(pitch) * glm::cos(yaw)
    );

    glm::vec3 right = glm::vec3(
            glm::sin(yaw - PI / 2.0f),
            0.0f,
            glm::cos(yaw - PI / 2.0f)
    );

    glm::vec3 up = glm::cross(right, -direction);

    projectionMatrix = glm::perspective(glm::radians(70.0f), (float) viewport.width / (float) viewport.height,
                                        0.01f, 512.0f);
    viewMatrix = glm::lookAt(eyePosition, eyePosition + direction, up);

    return cameraMatrix = (projectionMatrix * viewMatrix);
}

glm::mat4 Camera::GetMatrix() {
    return cameraMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
    return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() {
    return projectionMatrix;
}
