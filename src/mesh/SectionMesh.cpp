//
// Created by twome on 26/01/2020.
//

#include <iostream>
#include "SectionMesh.h"
#include "../NextCraft.h"
#include "Vertices.h"


using namespace chunk;

SectionMesh::SectionMesh(Section *section)
        : solidMesh(nullptr), state(State::RebuildScheduled), section(section), xo(section->x << 4),
          yo(section->y << 4),
          zo(section->z << 4) {

}

void SectionMesh::Render(RenderLayer layer) {
    if (state == State::RebuildScheduled) {
        state = State::AwaitingRebuild;
        AsyncMeshBuilder::Schedule(&section);
    } else if (state == State::UploadScheduled) {
        Upload();
        state = State::Rendering;
    } else if (state == State::Rendering) {
        if (layer == RenderLayer::Solid)
            solidVao.Draw();
        else if (hasFluidMesh)
            fluidVao.Draw();
    }
}

void SectionMesh::Build() {
    if (state != State::AwaitingRebuild)
        return;

    if (this->solidMesh == nullptr)
        this->solidMesh = new Mesh(35000);
    else
        this->solidMesh->Clear();

    if (hasFluidMesh) {
        if (this->fluidMesh == nullptr)
            this->fluidMesh = new Mesh(3000);
        else
            this->fluidMesh->Clear();
    }

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

                me.blockRenderer->Render(this, me, data, x, y, z, absX, absY, absZ);
            }
        }
    }

    state = State::UploadScheduled;
}

void SectionMesh::Upload() {
    if (state == State::Deleted || state == State::DeleteScheduled)
        return;

    solidVao.Initialize();
    solidVao.SetData(*solidMesh);

    delete solidMesh;
    solidMesh = nullptr;

    if (hasFluidMesh) {
        fluidVao.Initialize();
        fluidVao.SetData(*fluidMesh);

        delete fluidMesh;
        fluidMesh = nullptr;
    }
}

BlockData &SectionMesh::GetBlockData(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15)
        return NextCraft::GetWorld().GetBlockData(xo + x, yo + y, zo + z);
    else return section->GetBlockData(x, y, z);
}

SectionMesh::~SectionMesh() {
    section = nullptr;
    delete solidMesh;
}

Mesh *SectionMesh::GetSolidMesh() {
    return solidMesh;
}

Mesh *SectionMesh::GetFluidMesh() {
    return fluidMesh;
}

void SectionMesh::EnableFluidMesh() {
    hasFluidMesh = true;
}
