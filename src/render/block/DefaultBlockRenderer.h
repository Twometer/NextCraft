//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_DEFAULTBLOCKRENDERER_H
#define NEXTCRAFT_DEFAULTBLOCKRENDERER_H


#include "IBlockRenderer.h"

class DefaultBlockRenderer : public IBlockRenderer {
private:
    Texture topTex;
    Texture sideTex;
    Texture bottomTex;

public:
    DefaultBlockRenderer(const Texture &topTex, const Texture &sideTex, const Texture &bottomTex);

    void Render(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, int absX, int absY, int absZ) override;

    bool RequiresFluidMesh() const override;

private:
    bool ShouldRender(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, BlockFace face) const;
};


#endif //NEXTCRAFT_DEFAULTBLOCKRENDERER_H
