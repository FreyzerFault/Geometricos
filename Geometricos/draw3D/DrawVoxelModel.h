#pragma once

#include "Draw.h"
#include "DrawVoxel.h"
#include "VoxelModel.h"


namespace GEO
{
    class DrawVoxelModel {
        
        VoxelModel voxelModel;

        // Grid 3D de punteros a DrawVoxel
        std::vector<DrawVoxel> whiteVoxels;
        std::vector<DrawVoxel> blackVoxels;
        std::vector<DrawVoxel> greyVoxels;

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


