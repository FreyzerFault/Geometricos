#pragma once

#include "Voxel.h"
#include "VoxelGrid.h"

namespace GEO
{
	static double defaultVoxelSize = 0.2;

	class VoxelModel : public VoxelGrid
	{
		TriangleModel* triModel;
		
		std::vector<Voxel*> whiteVoxels;
		std::vector<Voxel*> greyVoxels;
		std::vector<Voxel*> blackVoxels;

	public:
		// El constructor es privado porque solo lo puede generar un TriangleModel
		VoxelModel(TriangleModel& triModel, double voxelSize);

		VoxelModel(const VoxelModel& orig) = default;

		// Comprueba que el punto esta dentro de la malla
		// Si el voxel que lo contiene es negro esta dentro
		// Si es blanco esta fuera, y si es gris comprobamos los triangulos
		bool pointIntoMesh(const Vec3D& point, bool checkTris = true, bool useRaycast = true) const;

		const TriangleModel* getTriModel() const { return triModel; }

		std::vector<Voxel*> getWhiteVoxels() { return whiteVoxels; }
		std::vector<Voxel*> getGreyVoxels() { return greyVoxels; }
		std::vector<Voxel*> getBlackVoxels() { return blackVoxels; }
	};
}
