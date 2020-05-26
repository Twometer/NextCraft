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

    delete mesh;
    this->mesh = new Mesh(35000);

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

                int tx = me.sideTex.x;
                int ty = me.sideTex.y;

                if (ShouldRender(&me, x + 1, y, z, 0))
                    PutVertices(PosXVertices, PosXTextures, absX, absY, absZ, tx, ty, 0, mesh);
                if (ShouldRender(&me, x - 1, y, z, 1))
                    PutVertices(NegXVertices, NegXTextures, absX, absY, absZ, tx, ty, 1, mesh);

                if (ShouldRender(&me, x, y, z + 1, 2))
                    PutVertices(PosZVertices, PosZTextures, absX, absY, absZ, tx, ty, 2, mesh);
                if (ShouldRender(&me, x, y, z - 1, 3))
                    PutVertices(NegZVertices, NegZTextures, absX, absY, absZ, tx, ty, 3, mesh);


                tx = me.topTex.x;
                ty = me.topTex.y;
                if (ShouldRender(&me, x, y + 1, z, 4))
                    PutVertices(PosYVertices, PosYTextures, absX, absY, absZ, tx, ty, 4, mesh);

                tx = me.bottomTex.x;
                ty = me.bottomTex.y;
                if (ShouldRender(&me, x, y - 1, z, 5))
                    PutVertices(NegYVertices, NegYTextures, absX, absY, absZ, tx, ty, 5, mesh);
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

bool SectionMesh::ShouldRender(const Block *me, int x, int y, int z, int f) {
    if (x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15)
        return NextCraft::client->world.GetBlockData(xo + x, yo + y, zo + z).id == 0;
    else return section->GetBlockData(x, y, z).id == 0;
}

void SectionMesh::PutVertices(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, int x, int y,
                              int z, int texX, int texY, int f, Mesh *mesh) {
    float brightness;
    switch (f) {
        case 0:
        case 1:
            brightness = 0.95;
            break;
        case 2:
        case 3:
            brightness = 0.85;
            break;
        case 4:
            brightness = 1.0f;
            break;
        case 5:
            brightness = 0.5f;
            break;
        default:
            brightness = 1.0f;
            break;
    }

    for (int i = 0; i < vertices.size(); i += 3) {
        GLfloat vx = vertices[i] + x;
        GLfloat vy = vertices[i + 1] + y;
        GLfloat vz = vertices[i + 2] + z;

        mesh->AddVertex(vx, vy, vz);
        mesh->AddColor(brightness, brightness, brightness);
    }

    const GLfloat d = 0.03125;

    for (int i = 0; i < textures.size(); i += 2) {
        GLfloat u = (textures[i] + static_cast<float>(texX)) * d;
        GLfloat v = (textures[i + 1] + static_cast<float>(texY)) * d;
        mesh->AddTexCoords(u, v);
    }
}