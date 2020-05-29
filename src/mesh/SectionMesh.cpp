//
// Created by twome on 26/01/2020.
//

#include <iostream>
#include "SectionMesh.h"
#include "../NextCraft.h"
#include "Vertices.h"

using namespace chunk;

SectionMesh::SectionMesh(Section *section)
        : mesh(nullptr), state(State::RebuildScheduled), section(section), xo(section->x << 4), yo(section->y << 4),
          zo(section->z << 4) {

}

void SectionMesh::Render() {
    if (state == State::RebuildScheduled) {
        state = State::AwaitingRebuild;
        AsyncMeshBuilder::Schedule(section);
    } else if (state == State::UploadScheduled) {
        Upload();
        state = State::Rendering;
    } else if (state == State::Rendering) {
        vao.Draw();
    }
}

void SectionMesh::Build() {
    if (state != State::AwaitingRebuild)
        return;

    if (this->mesh == nullptr)
        this->mesh = new Mesh(35000);
    else
        this->mesh->Clear();

    for (int x = 0; x < 16; x++) {
        int absX = x + xo;
        for (int y = 0; y < 16; y++) {
            int absY = y + yo;
            for (int z = 0; z < 16; z++) {
                int absZ = z + zo;
                const BlockData &data = section->GetBlockData(x, y, z);
                const Block &me = *BlockRegistry::Get(data.id);

                if (me.id == 0)
                    continue;

                me.blockRenderer->Render(this, me, x, y, z, absX, absY, absZ);
            }
        }
    }

    state = State::UploadScheduled;
}

void SectionMesh::Upload() {
    if (state == State::Deleted || state == State::DeleteScheduled)
        return;

    vao.Initialize();
    vao.SetData(*mesh);

    delete mesh;
    mesh = nullptr;
}

BlockData &SectionMesh::GetBlockData(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15)
        return NextCraft::GetWorld().GetBlockData(xo + x, yo + y, zo + z);
    else return section->GetBlockData(x, y, z);
}

SectionMesh::~SectionMesh() {
    delete mesh;
}

Mesh *SectionMesh::GetSolidMesh() {
    return mesh;
}
