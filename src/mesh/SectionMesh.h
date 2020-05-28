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

class SectionMesh {
private:
    chunk::Section *section = nullptr;

    Mesh *mesh = nullptr;

    State state;
    Vao vao;

    int xo;
    int yo;
    int zo;

    bool ShouldRender(const Block &me, int x, int y, int z, BlockFace face) const;

    inline chunk::BlockData &GetBlockData(int x, int y, int z) const;

    static void
    PutGeometry(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, int x, int y, int z,
                int texX, int texY, BlockFace face, Mesh *mesh);

    static bool CanOcclude(int x, int y, int z);

    static float GetOcclusionFactor(int x, int y, int z, int vx, int vy, int vz, BlockFace face);

public:
    explicit SectionMesh(chunk::Section *section);

    ~SectionMesh();

    void Render();

    void Build();

    void Upload();

};


#endif //NEXTCRAFT_SECTIONMESH_H
