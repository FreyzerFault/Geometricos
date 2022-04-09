#pragma once

#include "Voxel.h"

namespace GEO
{
	static double defaultVoxelSize = 0.2;

	class VoxelModel
	{
		const TriangleModel* triModel;

		Voxel*** voxelGrid;
		Vec3D gridSize;
		double voxelSize;

	public:
		// El constructor es privado porque solo lo puede generar un TriangleModel
		VoxelModel(const TriangleModel& triModel, double voxelSize);

		Voxel*** getVoxels() const { return voxelGrid; }

		// Comprueba que el punto esta dentro de la malla
		// Si el voxel que lo contiene es negro esta dentro
		// Si es blanco esta fuera, y si es gris comprobamos los triangulos
		bool pointIntoMesh(const Vec3D& point) const;

		Voxel* getVoxel(int x, int y, int z) const;
		Voxel* getVoxel(const Vec3D& point) const;

		Vec3D getGridSize() const { return gridSize; }

		double getVoxelSize() const { return voxelSize; }
	};
}
