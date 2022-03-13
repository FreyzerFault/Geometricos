#include "AABB.h"
#include "Triangle3D.h"
#include <iostream>


GEO::AABB::AABB()
{
}

GEO::AABB::AABB(const Vec3D& min, const Vec3D& max)
	: _min(min), _max(max)
{
}


GEO::Vec3D GEO::AABB::getCenter() const
{
	// El Extent pasa por el centro y esta a la mitad desde min a max
	return {getMin() + getExtent() / 2};
}

GEO::Vec3D GEO::AABB::getExtent() const
{
	return {_max - _min};
}
