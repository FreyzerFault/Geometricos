#include "Voxel.h"

#include "TriangleModel.h"

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
	for (const Triangle3D& face : triModel.getFaces())
	{
		if (AABBtri(face))
			tris.push_back(&face);
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

bool GEO::Voxel::contains(const Vec3D p) const
{
	for (const Vec3D& point : points)
	{
		if (point == p)
			return true;
	}
	return false;
}
