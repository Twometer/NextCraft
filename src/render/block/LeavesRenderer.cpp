//
// Created by twome on 29/05/2020.
//

#include "LeavesRenderer.h"

LeavesRenderer::LeavesRenderer(const Texture &texture)
        : DefaultBlockRenderer(texture, texture, texture) {}


bool LeavesRenderer::IsTransparent() {
    return true;
}

bool
LeavesRenderer::ShouldRender(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, BlockFace face) const {
    return true;
}