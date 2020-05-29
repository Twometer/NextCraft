//
// Created by twome on 29/05/2020.
//

#include "DefaultBlockRenderer.h"
#include "../../mesh/Vertices.h"
#include "../../model/block/BlockRegistry.h"

void DefaultBlockRenderer::Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y,
                                  int z, int absX, int absY, int absZ) {
    int tx = sideTex.x;
    int ty = sideTex.y;

    Mesh *mesh = sectionMesh->GetSolidMesh();

    if (ShouldRender(sectionMesh, me, x + 1, y, z, PosX))
        PutGeometry(PosXVertices, PosXTextures, absX, absY, absZ, tx, ty, PosX, mesh);
    if (ShouldRender(sectionMesh, me, x - 1, y, z, NegX))
        PutGeometry(NegXVertices, NegXTextures, absX, absY, absZ, tx, ty, NegX, mesh);

    if (ShouldRender(sectionMesh, me, x, y, z + 1, PosZ))
        PutGeometry(PosZVertices, PosZTextures, absX, absY, absZ, tx, ty, PosZ, mesh);
    if (ShouldRender(sectionMesh, me, x, y, z - 1, NegZ))
        PutGeometry(NegZVertices, NegZTextures, absX, absY, absZ, tx, ty, NegZ, mesh);

    tx = topTex.x;
    ty = topTex.y;
    if (ShouldRender(sectionMesh, me, x, y + 1, z, PosY))
        PutGeometry(PosYVertices, PosYTextures, absX, absY, absZ, tx, ty, PosY, mesh);

    tx = bottomTex.x;
    ty = bottomTex.y;
    if (ShouldRender(sectionMesh, me, x, y - 1, z, NegY))
        PutGeometry(NegYVertices, NegYTextures, absX, absY, absZ, tx, ty, NegY, mesh);
}

bool DefaultBlockRenderer::ShouldRender(SectionMesh *sectionMesh, const Block &me, int x, int y, int z,
                                        BlockFace face) const {
    chunk::BlockData &data = sectionMesh->GetBlockData(x, y, z);
    if (data.id == 0)
        return true;

    Block *other = BlockRegistry::Get(data.id);
    if (other->blockRenderer->IsTransparent())
        return true;
    return ((other->id == 8 || other->id == 9) && !(me.id == 8 || me.id == 9));
}

DefaultBlockRenderer::DefaultBlockRenderer(const Texture &topTex, const Texture &sideTex, const Texture &bottomTex)
        : topTex(topTex), sideTex(sideTex), bottomTex(bottomTex) {
}
