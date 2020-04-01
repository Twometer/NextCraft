//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_SECTIONMESH_H
#define NEXTCRAFT_SECTIONMESH_H

#include "Vao.h"
#include "../model/world/Section.h"
#include "../model/block/Block.h"

enum class State {
    RebuildScheduled,
    UploadScheduled,
    DeleteScheduled,
    AwaitingRebuild,
    Rendering,
    Deleted
};

namespace chunk {
    class Section;
}

class SectionMesh {
private:
    chunk::Section *section = nullptr;

    Mesh *mesh = nullptr;

    State state;
    Vao vao;

    int xo;
    int yo;
    int zo;

    bool ShouldRender(const Block *me, int x, int y, int z, int f);

    void PutVertices(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, int x, int y, int z,
                     int texX, int texY, Mesh *mesh);

public:
    explicit SectionMesh(chunk::Section *section);

    void Render();

    void Build();

    void Upload();

};


#endif //NEXTCRAFT_SECTIONMESH_H
