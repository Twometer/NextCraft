//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_TIMER_H
#define NEXTCRAFT_TIMER_H

#include <GLFW/glfw3.h>

class Timer {
private:
    float lastTick = 0.0f;

    float ms = 0.0f;

    static float GetTime() {
        return (float) glfwGetTime();
    }

public:
    void Begin(float tps) {
        ms = 1.f / tps;
        Reset();
    }

    bool HasReached() {
        return glfwGetTime() >= lastTick + ms;
    }

    void Reset() {
        lastTick = GetTime();
    }
};

#endif //NEXTCRAFT_TIMER_H
