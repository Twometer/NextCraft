//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_PLANTRENDERER_H
#define NEXTCRAFT_PLANTRENDERER_H


#include "IBlockRenderer.h"

class PlantRenderer : public IBlockRenderer {
private:
    Texture texture;

public:
    explicit PlantRenderer(const Texture &texture);

    void Render(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, int absX, int absY, int absZ) override;

    bool IsTransparent() override;
};


#endif //NEXTCRAFT_PLANTRENDERER_H
