//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_SECTIONMESH_H
#define NEXTCRAFT_SECTIONMESH_H

#include "../gl/Vao.h"
#include "../model/world/Section.h"
#include "../model/world/BlockData.h"
#include "../model/block/Block.h"
#include "../model/block/BlockFace.h"

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

class IBlockRenderer;

class SectionMesh {
private:
    chunk::Section *section = nullptr;

    Mesh *mesh = nullptr;

    State state;
    Vao vao;

    int xo;
    int yo;
    int zo;

public:
    explicit SectionMesh(chunk::Section *section);

    ~SectionMesh();

    void Render();

    void Build();

    void Upload();

    Mesh *GetSolidMesh();

    chunk::BlockData &GetBlockData(int x, int y, int z) const;
};


#endif //NEXTCRAFT_SECTIONMESH_H
