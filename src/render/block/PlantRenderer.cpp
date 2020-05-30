//
// Created by twome on 29/05/2020.
//

#include "PlantRenderer.h"
#include "../../mesh/Vertices.h"

PlantRenderer::PlantRenderer(const Sprite &texture) : texture(texture) {
}

void
PlantRenderer::Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z,
                      int absX, int absY, int absZ) {
    PutGeometry(PlantVertices, PlantTextures, absX, absY, absZ, texture.x, texture.y, PosX,
                sectionMesh->GetSolidMesh());
}

bool PlantRenderer::IsTransparent() const {
    return true;
}
