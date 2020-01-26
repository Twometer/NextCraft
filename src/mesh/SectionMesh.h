//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_SECTIONMESH_H
#define NEXTCRAFT_SECTIONMESH_H

#include "Vao.h"
#include "../model/world/Section.h"

enum class State {
    RebuildScheduled,
    UploadScheduled,
    DeleteScheduled,
    Rendering,
    Waiting,
    Deleted
};

namespace chunk {
    class Section;
}

class SectionMesh {
private:
    chunk::Section *section;

    State state;

    Vao vao;

    int xo;
    int yo;
    int zo;

public:
    explicit SectionMesh(chunk::Section *section);

    void Render();

    void Build();

    void Upload();

};


#endif //NEXTCRAFT_SECTIONMESH_H
