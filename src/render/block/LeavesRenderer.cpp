//
// Created by twome on 29/05/2020.
//

#include "LeavesRenderer.h"

LeavesRenderer::LeavesRenderer(const Texture &texture)
        : DefaultBlockRenderer(texture, texture, texture) {}

void
LeavesRenderer::Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z,
                       int absX, int absY, int absZ) {
    switch (data.meta & 3) {
        case 1:
            topTex = sideTex = bottomTex = {18, 6};
            break;
        case 2:
            topTex = sideTex = bottomTex = {15, 6};
            break;
        case 3:
            topTex = sideTex = bottomTex = {16, 6};
            break;
    }

    DefaultBlockRenderer::Render(sectionMesh, me, data, x, y, z, absX, absY, absZ);
}

bool LeavesRenderer::IsTransparent() const {
    return true;
}

bool
LeavesRenderer::ShouldRender(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, BlockFace face) const {
    return true;
}