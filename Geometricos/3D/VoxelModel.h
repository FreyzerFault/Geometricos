#pragma once
#include <map>

#include "TriangleModel.h"
#include "Voxel.h"

namespace GEO
{

	class VoxelModel
	{
		TriangleModel* triModel;
		std::vector<Voxel> voxels;

	public:
		VoxelModel(TriangleModel& triModel, double voxelSize);

		std::vector<Voxel> getVoxels() const { return voxels; }

	};
}
