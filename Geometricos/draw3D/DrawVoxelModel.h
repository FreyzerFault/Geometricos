#pragma once

#include "Scene.h"
#include "Draw.h"
#include "DrawVoxel.h"
#include "VoxelModel.h"


namespace GEO
{
    class DrawVoxelModel : public Draw {

        VoxelModel vm;

        std::vector<DrawVoxel> dv;

    public:

        DrawVoxelModel(const VoxelModel& vm);

        DrawVoxelModel(const DrawVoxelModel& dvm) : Draw(), vm(dvm.vm) {}

        void drawIt();

        ~DrawVoxelModel() override = default;;
    };

}


