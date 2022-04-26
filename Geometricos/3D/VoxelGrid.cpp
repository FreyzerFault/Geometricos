﻿#include "VoxelGrid.h"

#include "PointCloud3D.h"
#include "Voxel.h"

GEO::VoxelGrid::VoxelGrid(const Vec3D& gridSize, double voxelSize, const Vec3D& origin)
	: gridSize(gridSize), voxelSize(voxelSize), aabb(origin, origin + gridSize * voxelSize)
{
	std::cout << "Creando VoxelGrid con " << gridSize.getX() << " * "  << gridSize.getY() << " * " << gridSize.getZ() << " voxels..." << std::endl;

	// Reservamos espacio para la Malla 3D:
	grid = new Voxel**[gridSize.getX()];

	for (int x = 0; x < gridSize.getX(); ++x)
	{
		grid[x] = new Voxel*[gridSize.getY()];

		for (int y = 0; y < gridSize.getY(); ++y)
		{
			grid[x][y] = new Voxel[gridSize.getZ()];

			// Creamos los Voxeles
			for (int z = 0; z < gridSize.getZ(); ++z)
			{
				// Esquina inferior del voxel
				Vec3D voxelMin(x,y,z);
				voxelMin = voxelMin * voxelSize + origin;

				// Esquina superior
				Vec3D voxelMax = voxelMin + voxelSize;
				
				grid[x][y][z] = Voxel(voxelMin, voxelMax, this);
			}
		}
	}
}

// Crea la VoxelGrid a partir de un AABB con un tamaño de Voxel
// Si se pasa de tamaño le cogemos el ceil para no quedarnos cortos
GEO::VoxelGrid::VoxelGrid(double voxelSize, const AABB& aabb)
	: VoxelGrid(Vec3D(aabb.getExtent() / voxelSize).ceil(), voxelSize, aabb.getMin())
{
}

GEO::VoxelGrid::VoxelGrid(double voxelSize, const PointCloud3D& cloud)
	: VoxelGrid(voxelSize, cloud.getAABB())
{
	addPoints(cloud.getPoints());
}

std::vector<std::pair<GEO::Voxel*, int>> GEO::VoxelGrid::voxelsMasPoblados(int numVoxels) const
{
	std::vector<std::pair<Voxel*, int>> bestVoxels;
	bestVoxels.reserve(numVoxels);

	int minPoblacion = BasicGeom::INFINITO;
	int minIndex = 0;

	for (int x = 0; x < gridSize.getX(); ++x)
	for (int y = 0; y < gridSize.getY(); ++y)
	for (int z = 0; z < gridSize.getZ(); ++z)
	{
		Voxel* voxel = &grid[x][y][z];
		// Una heuristica sera cuan de cerca este el voxel de los demas seleccionados
		// Si es mayor a 3 voxeles, lo ignoramos
		// Como minimo cada voxel seleccionado estara a 3 voxeles de distancia de los demas
		bool voxelNear = false;
		for (auto && [bestVoxel, pobl] : bestVoxels)
		{
			if (voxel->getCenter().distance(bestVoxel->getCenter()) < voxelSize * 1)
			{
				voxelNear = true;
				break;
			}
		}
		if (voxelNear)
			break;
		
		const double poblacion = voxel->poblacionCercana();

		// Primero rellenamos el vector con los primeros voxeles
		if (bestVoxels.size() < numVoxels)
		{
			bestVoxels.emplace_back(voxel, poblacion);

			if (poblacion < minPoblacion)
			{
				minPoblacion = poblacion;
				minIndex = numVoxels - 1;
			}
		}
		// Cuando este lleno, si tiene una poblacion mayor que el Minimo hasta ahora
		// Sustituimos el que tenga menos poblacion
		else if (poblacion > minPoblacion)
		{
			bestVoxels[minIndex] = std::make_pair(voxel, poblacion);

			// Buscamos el nuevo minimo
			for (int i = 0; i < bestVoxels.size(); i++)
				if (bestVoxels[i].second < minPoblacion)
				{
					minPoblacion = bestVoxels[i].second;
					minIndex = i;
					break;
				}
		}
	}
	return bestVoxels;
}

GEO::Voxel* GEO::VoxelGrid::addPoint(const Vec3D& point) const
{
	Voxel* voxel = getVoxel(point);

	if (voxel == nullptr)
		return nullptr;

	voxel->add(point);
	return voxel;
}

void GEO::VoxelGrid::addPoints(const std::vector<Vec3D>& points) const
{
	for (auto& point : points)
	{
		addPoint(point);
	}
}

GEO::Voxel* GEO::VoxelGrid::getVoxel(int x, int y, int z) const
{
	if (x >= gridSize.getX() || y >= gridSize.getY() || z >= gridSize.getZ() || x < 0 || y < 0 || z < 0)
		return nullptr;

	return &grid[x][y][z];
}

GEO::Voxel* GEO::VoxelGrid::getVoxel(const Vec3D& point) const
{
	if (!aabb.pointInAABB(point))
		return nullptr;

	const Vec3D localPosition = point - aabb.getMin();

	const int x = std::floor(localPosition.getX() / voxelSize);
	const int y = std::floor(localPosition.getY() / voxelSize);
	const int z = std::floor(localPosition.getZ() / voxelSize);

	return getVoxel(x,y,z);
}

GEO::Vec3D GEO::VoxelGrid::getVoxelCoords(const Voxel& voxel) const
{
	const Vec3D localPosition = voxel.getCenter() - aabb.getMin();

	const double x = std::floor(localPosition.getX() / voxelSize);
	const double y = std::floor(localPosition.getY() / voxelSize);
	const double z = std::floor(localPosition.getZ() / voxelSize);

	return {x,y,z};
}
