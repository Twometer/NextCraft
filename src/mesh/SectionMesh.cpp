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

                int tx = me.sideTex.x;
                int ty = me.sideTex.y;

                if (ShouldRender(me, x + 1, y, z, PosX))
                    PutGeometry(PosXVertices, PosXTextures, absX, absY, absZ, tx, ty, PosX, mesh);
                if (ShouldRender(me, x - 1, y, z, NegX))
                    PutGeometry(NegXVertices, NegXTextures, absX, absY, absZ, tx, ty, NegX, mesh);

                if (ShouldRender(me, x, y, z + 1, PosZ))
                    PutGeometry(PosZVertices, PosZTextures, absX, absY, absZ, tx, ty, PosZ, mesh);
                if (ShouldRender(me, x, y, z - 1, NegZ))
                    PutGeometry(NegZVertices, NegZTextures, absX, absY, absZ, tx, ty, NegZ, mesh);

                tx = me.topTex.x;
                ty = me.topTex.y;
                if (ShouldRender(me, x, y + 1, z, PosY))
                    PutGeometry(PosYVertices, PosYTextures, absX, absY, absZ, tx, ty, PosY, mesh);

                tx = me.bottomTex.x;
                ty = me.bottomTex.y;
                if (ShouldRender(me, x, y - 1, z, NegY))
                    PutGeometry(NegYVertices, NegYTextures, absX, absY, absZ, tx, ty, NegY, mesh);
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

bool SectionMesh::ShouldRender(const Block &me, int x, int y, int z, BlockFace face) const {
    BlockData &data = GetBlockData(x, y, z);
    if (data.id == 0)
        return true;

    Block *other = BlockRegistry::Get(data.id);
    return (other->id == 8 || other->id == 9) && !(me.id == 8 || me.id == 9);
}

BlockData &SectionMesh::GetBlockData(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0 || x > 15 || y > 15 || z > 15)
        return NextCraft::client->world.GetBlockData(xo + x, yo + y, zo + z);
    else return section->GetBlockData(x, y, z);
}

void SectionMesh::PutGeometry(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, int x, int y,
                              int z, int texX, int texY, BlockFace face, Mesh *mesh) {
    float brightness;
    switch (face) {
        case PosX:
        case NegX:
            brightness = 0.85;
            break;
        case PosZ:
        case NegZ:
            brightness = 0.65;
            break;
        case NegY:
            brightness = 0.55;
            break;
        case PosY:
        default:
            brightness = 1.0f;
            break;
    }

    for (int i = 0; i < vertices.size(); i += 3) {
        GLfloat vx = vertices[i];
        GLfloat vy = vertices[i + 1];
        GLfloat vz = vertices[i + 2];
        mesh->AddVertex(vx + x, vy + y, vz + z);

        float vertexBrightness = brightness * GetOcclusionFactor(x, y, z, (int) vx, (int) vy, (int) vz, face);
        mesh->AddColor(vertexBrightness, vertexBrightness, vertexBrightness);
    }

    const GLfloat d = 0.03125;

    for (int i = 0; i < textures.size(); i += 2) {
        GLfloat u = (textures[i] + static_cast<float>(texX)) * d;
        GLfloat v = (textures[i + 1] + static_cast<float>(texY)) * d;
        mesh->AddTexCoords(u, v);
    }
}

SectionMesh::~SectionMesh() {
    delete mesh;
}

bool SectionMesh::CanOcclude(int x, int y, int z) {
    BlockData &data = NextCraft::client->world.GetBlockData(x, y, z);
    return !(data.id == 8 || data.id == 9 || data.id == 0);
}

float SectionMesh::GetOcclusionFactor(int x, int y, int z, int vx, int vy, int vz, BlockFace face) {
    if (vx == 0) vx = -1;
    if (vy == 0) vy = -1;
    if (vz == 0) vz = -1;

    switch (face) {
        case PosX:
        case NegX: {
            float oc = 1.0f;
            if (CanOcclude(x + vx, y + vy, z)) oc -= 0.2;
            if (CanOcclude(x + vx, y + vy, z + vz)) oc -= 0.2;
            if (CanOcclude(x + vx, y, z + vz)) oc -= 0.2;
            return oc;
        }
        case PosY:
        case NegY: {
            float oc = 1.0f;
            if (CanOcclude(x + vx, y + vy, z)) oc -= 0.2;
            if (CanOcclude(x, y + vy, z + vz)) oc -= 0.2;
            if (CanOcclude(x + vx, y + vy, z + vz)) oc -= 0.2;
            return oc;
        }
        case PosZ:
        case NegZ: {
            float oc = 1.0f;
            if (CanOcclude(x + vx, y, z + vz)) oc -= 0.2;
            if (CanOcclude(x, y + vy, z + vz)) oc -= 0.2;
            if (CanOcclude(x + vx, y + vy, z + vz)) oc -= 0.2;
            return oc;
        }
        default:
            break;
    }
    return 1.0f;
}
