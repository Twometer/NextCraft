//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_DEFAULTBLOCKRENDERER_H
#define NEXTCRAFT_DEFAULTBLOCKRENDERER_H


#include "IBlockRenderer.h"

class DefaultBlockRenderer : public IBlockRenderer {
protected:
    Sprite topTex;
    Sprite sideTex;
    Sprite bottomTex;

public:
    DefaultBlockRenderer(const Sprite &topTex, const Sprite &sideTex, const Sprite &bottomTex);

    void Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z, int absX,
                int absY, int absZ) override;

protected:
    virtual bool ShouldRender(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, BlockFace face) const;
};


#endif //NEXTCRAFT_DEFAULTBLOCKRENDERER_H
