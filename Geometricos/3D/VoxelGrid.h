#pragma once
#include "AABB.h"
#include "Vec3D.h"

namespace GEO
{
	class PointCloud3D;
	class AABB;
	class Voxel;

	class VoxelGrid
	{
	protected:
		Voxel*** grid;
		Vec3D gridSize; // Num Voxels en cada Coord
		double voxelSize; // Tamaño de Voxel

		AABB aabb;

	public:
		VoxelGrid(const Vec3D& gridSize, double voxelSize, const Vec3D& origin);
		VoxelGrid(double voxelSize, const AABB& aabb);
		VoxelGrid(double voxelSize, const PointCloud3D& cloud);

		std::vector<std::pair<Voxel*, int>> voxelsMasPoblados(int numVoxels = 1) const;

		Voxel* addPoint(const Vec3D& point) const;
		void addPoints(const std::vector<Vec3D>& points) const;

		Voxel* getVoxel(int x, int y, int z) const;
		Voxel* getVoxel(const Vec3D& point) const;
		Vec3D getVoxelCoords(const Voxel& voxel) const;

		Voxel*** getGrid() const { return grid; }

		AABB getAABB() const { return aabb; }

		double getVoxelSize() const { return voxelSize; }
		Vec3D getGridSize() const { return gridSize; }
	};
}
