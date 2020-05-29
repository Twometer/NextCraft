//
// Created by twome on 29/05/2020.
//

#include "IBlockRenderer.h"
#include "../../NextCraft.h"

void
IBlockRenderer::PutGeometry(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, int x, int y,
                            int z, int texX, int texY, BlockFace face, Mesh *mesh) const {
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

        float vertexBrightness = IsShaded() ? brightness *
                                              GetOcclusionFactor(x, y, z, (int) vx, (int) vy, (int) vz, face) : 1.0f;
        mesh->AddColor(vertexBrightness, vertexBrightness, vertexBrightness);
    }

    const GLfloat d = 0.03125;

    for (int i = 0; i < textures.size(); i += 2) {
        GLfloat u = (textures[i] + static_cast<float>(texX)) * d;
        GLfloat v = (textures[i + 1] + static_cast<float>(texY)) * d;
        mesh->AddTexCoords(u, v);
    }
}

bool IBlockRenderer::CanOcclude(int x, int y, int z) {
    chunk::BlockData &data = NextCraft::GetWorld().GetBlockData(x, y, z);
    return !(data.id == 8 || data.id == 9 || data.id == 0 || data.id == 31);
}

float IBlockRenderer::GetOcclusionFactor(int x, int y, int z, int vx, int vy, int vz, BlockFace face) {
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

bool IBlockRenderer::IsShaded() const {
    return true;
}

bool IBlockRenderer::RequiresFluidMesh() const {
    return false;
}

bool IBlockRenderer::IsTransparent() const {
    return false;
}

IBlockRenderer::~IBlockRenderer() = default;
