//
// Created by twome on 29/05/2020.
//

#include <iostream>
#include "InputHandler.h"
#include "../NextCraft.h"

void InputHandler::HandleInput() {
    if (!NextCraft::GetClient().IsReady())
        return;

    GLFWwindow *window = NextCraft::window;
    Player &player = NextCraft::GetPlayer();

    bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
    if (!focused) return;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (0 != mouseX || 0 != mouseY) {
        player.yaw -= 0.125f * (float) mouseX;
        player.pitch -= 0.125f * (float) mouseY;

        player.pitch = glm::clamp(player.pitch, -90.f, 90.f);
        glfwSetCursorPos(window, 0, 0);
    }

    float yaw = glm::radians(player.yaw);
    glm::vec3 direction(glm::sin(yaw), 0, glm::cos(yaw));

    const float speedMultiplier = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ? 0.045 : 0.025f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.AddVelocity(direction * speedMultiplier);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm::vec3 directionLeft(direction.z, 0, -direction.x);
        player.AddVelocity(directionLeft * speedMultiplier);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player.AddVelocity(-direction * speedMultiplier);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm::vec3 directionRight(-direction.z, 0, direction.x);
        player.AddVelocity(directionRight * speedMultiplier);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (player.flying)
            player.motionY = 0.2f;
        else
            player.Jump();

        if (!spacebarHeld && !player.onGround && glfwGetTime() - prevSpacebarHit < 0.25 &&
            player.gameMode == GameMode::Creative) {
            player.flying = !player.flying;
        }

        prevSpacebarHit = glfwGetTime();
        spacebarHeld = true;
    } else spacebarHeld = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        if (player.flying)
            player.motionY = -0.2f;
    }

    // Wait for some time before enabling physics
    // to prevent player falling through the ground
    if (physicsWaitTicks < PHYSICS_DELAY)
        physicsWaitTicks++;
    else
        player.Update();
    lookingAt = raycast.CastRay();
}

const RaycastResult &InputHandler::GetLookingAt() const {
    return lookingAt;
}
