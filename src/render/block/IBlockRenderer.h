//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_IBLOCKRENDERER_H
#define NEXTCRAFT_IBLOCKRENDERER_H

#include "../../model/block/BlockFace.h"
#include "../../mesh/SectionMesh.h"

struct Block;

class SectionMesh;

class IBlockRenderer {
public:
    virtual ~IBlockRenderer();

    virtual void
    Render(SectionMesh *sectionMesh, const Block &me, int x, int y, int z, int absX, int absY, int absZ) = 0;

    virtual bool RequiresFluidMesh() const;

    virtual bool IsShaded() const;

    virtual bool IsTransparent();

protected:
    void PutGeometry(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, int x, int y, int z,
                     int texX, int texY, BlockFace face, Mesh *mesh) const;

    static bool CanOcclude(int x, int y, int z);

    static float GetOcclusionFactor(int x, int y, int z, int vx, int vy, int vz, BlockFace face);
};


#endif //NEXTCRAFT_IBLOCKRENDERER_H
