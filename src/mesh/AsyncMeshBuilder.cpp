//
// Created by twome on 26/01/2020.
//

#include "AsyncMeshBuilder.h"
#include "../util/Logger.h"

bool AsyncMeshBuilder::running = true;
moodycamel::ConcurrentQueue<chunk::Section **> *AsyncMeshBuilder::concurrentQueue;

void AsyncMeshBuilder::Work() {

    while (running) {
        chunk::Section **secPtr;
        if (concurrentQueue->try_dequeue(secPtr)) {
            chunk::Section *sec = *secPtr;
            if (sec != nullptr)
                sec->mesh->Build();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}

void AsyncMeshBuilder::Initialize() {
    Logger::Info("Initializing mesh builder queue");

    concurrentQueue = new moodycamel::ConcurrentQueue<chunk::Section **>();

    for (int i = 0; i < 16; i++) {
        new std::thread(&AsyncMeshBuilder::Work);
    }
}

void AsyncMeshBuilder::Schedule(chunk::Section **section) {
    concurrentQueue->enqueue(section);
}

void AsyncMeshBuilder::Shutdown() {
    running = false;
    delete concurrentQueue;
}
