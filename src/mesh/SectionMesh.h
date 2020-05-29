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
#include "../render/RenderLayer.h"

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

    Mesh *solidMesh = nullptr;
    Mesh *fluidMesh = nullptr;

    State state;
    Vao solidVao;
    Vao fluidVao;

    bool hasFluidMesh;

    int xo;
    int yo;
    int zo;

public:
    explicit SectionMesh(chunk::Section *section);

    ~SectionMesh();

    void Render(RenderLayer layer);

    void Build();

    void Upload();

    void EnableFluidMesh();

    Mesh *GetSolidMesh();

    Mesh *GetFluidMesh();

    chunk::BlockData &GetBlockData(int x, int y, int z) const;
};


#endif //NEXTCRAFT_SECTIONMESH_H
