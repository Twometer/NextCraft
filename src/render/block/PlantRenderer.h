//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_PLANTRENDERER_H
#define NEXTCRAFT_PLANTRENDERER_H


#include "IBlockRenderer.h"

class PlantRenderer : public IBlockRenderer {
private:
    Sprite texture;

public:
    explicit PlantRenderer(const Sprite &texture);

    void Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z, int absX,
                int absY, int absZ) override;

    bool IsTransparent() const override;
};


#endif //NEXTCRAFT_PLANTRENDERER_H
