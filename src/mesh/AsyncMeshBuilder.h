//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_ASYNCMESHBUILDER_H
#define NEXTCRAFT_ASYNCMESHBUILDER_H


#include <concurrentqueue.h>
#include "../model/world/Section.h"

class AsyncMeshBuilder {
private:
    static bool running;

    static moodycamel::ConcurrentQueue<chunk::Section **> *concurrentQueue;

    static void Work();

public:
    static void Initialize();

    static void Schedule(chunk::Section **section);

    static void Shutdown();

};


#endif //NEXTCRAFT_ASYNCMESHBUILDER_H
