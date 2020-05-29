//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_LEAVESRENDERER_H
#define NEXTCRAFT_LEAVESRENDERER_H

#include "DefaultBlockRenderer.h"

class LeavesRenderer : public DefaultBlockRenderer {

public:
    LeavesRenderer(const Texture &texture);

    bool IsTransparent() const override;

    void Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z, int absX,
                int absY, int absZ) override;

protected:
    bool ShouldRender(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, BlockFace face) const override;

};


#endif //NEXTCRAFT_LEAVESRENDERER_H
