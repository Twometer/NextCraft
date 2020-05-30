//
// Created by twome on 29/05/2020.
//

#include "FluidRenderer.h"
#include "../../mesh/Vertices.h"
#include "../../model/block/BlockRegistry.h"

void FluidRenderer::Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z,
                           int absX, int absY, int absZ) {
    Mesh *mesh = sectionMesh->GetFluidMesh();

    if (ShouldRender(sectionMesh, x + 1, y, z))
        PutGeometry(PosXVertices, PosXTextures, absX, absY, absZ, texture.x, texture.y, PosX, mesh);
    if (ShouldRender(sectionMesh, x - 1, y, z))
        PutGeometry(NegXVertices, NegXTextures, absX, absY, absZ, texture.x, texture.y, NegX, mesh);
    if (ShouldRender(sectionMesh, x, y, z + 1))
        PutGeometry(PosZVertices, PosZTextures, absX, absY, absZ, texture.x, texture.y, PosZ, mesh);
    if (ShouldRender(sectionMesh, x, y, z - 1))
        PutGeometry(NegZVertices, NegZTextures, absX, absY, absZ, texture.x, texture.y, NegZ, mesh);
    if (ShouldRender(sectionMesh, x, y + 1, z))
        PutGeometry(PosYVertices, PosYTextures, absX, absY - 0.1f, absZ, texture.x, texture.y, PosY, mesh);
    if (ShouldRender(sectionMesh, x, y - 1, z))
        PutGeometry(NegYVertices, NegYTextures, absX, absY, absZ, texture.x, texture.y, NegY, mesh);
}

bool FluidRenderer::RequiresFluidMesh() const {
    return true;
}

bool FluidRenderer::IsTransparent() const {
    return true;
}

bool FluidRenderer::IsShaded() const {
    return false;
}

FluidRenderer::FluidRenderer(const Sprite &texture) : texture(texture) {}

bool FluidRenderer::ShouldRender(SectionMesh *mesh, int x, int y, int z) {
    chunk::BlockData &data = mesh->GetBlockData(x, y, z);
    Block *block = BlockRegistry::Get(data.id);
    return !block->blockRenderer->IsTransparent();
}
