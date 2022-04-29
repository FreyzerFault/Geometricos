#pragma once

#include "Draw.h"
#include "DrawVoxel.h"
#include "VoxelModel.h"


namespace GEO
{
    class DrawVoxelModel {
        
        VoxelModel voxelModel;

        Draw* WhiteDraw;
        Draw* BlackDraw;
        Draw* GreyDraw;

    public:

        DrawVoxelModel(VoxelModel vm);

        DrawVoxelModel(const DrawVoxelModel& dvm) : voxelModel(dvm.voxelModel) {}

        GEO::Draw* drawIt(TypeVoxel type = TypeVoxel::intersect);

        ~DrawVoxelModel() = default;
    };

}


