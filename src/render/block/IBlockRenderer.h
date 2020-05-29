//
// Created by twome on 29/05/2020.
//

#ifndef NEXTCRAFT_IBLOCKRENDERER_H
#define NEXTCRAFT_IBLOCKRENDERER_H

#include "../../model/block/BlockFace.h"
#include "../../model/world/BlockData.h"
#include "../../mesh/SectionMesh.h"

struct Block;

class SectionMesh;

class IBlockRenderer {
public:
    virtual ~IBlockRenderer();

    virtual void
    Render(SectionMesh *sectionMesh, const Block &me, const chunk::BlockData &data, int x, int y, int z, int absX,
           int absY, int absZ) = 0;

    virtual bool RequiresFluidMesh() const;

    virtual bool IsShaded() const;

    virtual bool IsTransparent() const;

protected:
    void
    PutGeometry(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &textures, float x, float y, float z,
                int texX, int texY, BlockFace face, Mesh *mesh) const;

    static bool CanOcclude(int x, int y, int z);

    static float GetOcclusionFactor(int x, int y, int z, int vx, int vy, int vz, BlockFace face);
};


#endif //NEXTCRAFT_IBLOCKRENDERER_H

