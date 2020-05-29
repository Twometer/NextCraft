//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_FLUIDRENDERER_H
#define NEXTCRAFT_FLUIDRENDERER_H


#include "IBlockRenderer.h"

class FluidRenderer : public IBlockRenderer {
private:
    Texture texture;

public:
    explicit FluidRenderer(const Texture &texture);

    void Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z, int absX,
                int absY, int absZ) override;

    bool RequiresFluidMesh() const override;

    bool IsTransparent() const override;

    static bool ShouldRender(SectionMesh *mesh, int x, int y, int z);

    bool IsShaded() const override;
};


#endif //NEXTCRAFT_FLUIDRENDERER_H
