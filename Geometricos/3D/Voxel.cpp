#include "Voxel.h"

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

GEO::TypeColor GEO::Voxel::getColor() const
{
	switch (type)
	{
	case TypeVoxel::black:
		return black;
	case TypeVoxel::white:
		return white;
	case TypeVoxel::grey:
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
