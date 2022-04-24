#include "Voxel.h"

#include "TriangleModel.h"

GEO::Voxel::Voxel(const Vec3D& min, const Vec3D& max, VoxelGrid* voxelGrid)
	: AABB(min, max), voxelGrid(voxelGrid)
{
	if (voxelGrid)
		gridCoord = voxelGrid->getVoxelCoords(*this);
}

bool GEO::Voxel::remove(const Vec3D& p)
{
	for (auto it = points.begin(); it != points.end(); ++it)
	{
		if (*it == p)
		{
			points.erase(it);
			return true;
		}
	}
	return false;
}

void GEO::Voxel::checkTris(const TriangleModel& triModel)
{
	for (const Triangle3D& tri : triModel.getTris())
	{
		if (AABBtri(tri))
		{
			tris.push_back(&tri);
			break;
		}
	}

	// Si intersecta con cualquier triangulo, intersecta con la malla
	if (!tris.empty())
		type = TypeVoxel::intersect;
	else
	{
		// Comprobamos si esta fuera o dentro
		if (triModel.pointIntoMesh(getCenter()))
			type = TypeVoxel::in;
		else
			type = TypeVoxel::out;
	}
}

int GEO::Voxel::poblacionCercana() const
{
	int poblacion = 0;
	constexpr int neighbourhoodSize = 3;
	for (int x = gridCoord.getX(); x < gridCoord.getX() + neighbourhoodSize; ++x)
	for (int y = gridCoord.getY(); y < gridCoord.getY() + neighbourhoodSize; ++y)
	for (int z = gridCoord.getZ(); z < gridCoord.getZ() + neighbourhoodSize; ++z)
	{
		Voxel* voxel = voxelGrid->getVoxel(x,y,z);
		if (voxel != nullptr)
			poblacion += voxelGrid->getVoxel(x,y,z)->poblacion();
	}
	return poblacion;
}


GEO::TypeColor GEO::Voxel::getColor() const
{
	switch (type)
	{
	case TypeVoxel::in:
		return black;
	case TypeVoxel::out:
		return white;
	case TypeVoxel::intersect:
		return grey;
	default:
		return red;// Rojo si no se ha procesado bien
	}
	
}

bool GEO::Voxel::contains(const Vec3D& p) const
{
	for (const Vec3D& point : points)
	{
		if (point == p)
			return true;
	}
	return false;
}
