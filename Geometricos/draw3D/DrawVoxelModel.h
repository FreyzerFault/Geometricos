#pragma once

#include "Draw.h"
#include "DrawVoxel.h"
#include "VoxelModel.h"


namespace GEO
{
    class DrawVoxelModel : public Draw {

        VoxelModel vm;

        // Grid 3D de punteros a DrawVoxel
        DrawVoxel**** dv;

    public:

        DrawVoxelModel(VoxelModel vm);

        DrawVoxelModel(const DrawVoxelModel& dvm) : Draw(), vm(dvm.vm) {}

        void drawIt(TypeVoxel type = TypeVoxel::intersect);

        ~DrawVoxelModel() override;
    };

}


