#include "AABB.h"
#include "Triangle3D.h"
#include <iostream>


GEO::AABB::AABB()
{
}

GEO::AABB::AABB(Vec3D & min, Vec3D & max)
	: _min(min), _max(max)
{
}

GEO::AABB::AABB(const AABB & aabb)
	: _min(aabb._min), _max(aabb._max)
{
}

GEO::AABB::~AABB()
{
}


GEO::Vec3D GEO::AABB::getCenter()
{
	//XXXX
	return Vec3D();
}

GEO::Vec3D GEO::AABB::getExtent()
{
	//XXXX
	return Vec3D();
}

GEO::AABB & GEO::AABB::operator=(const AABB & orig)
{
	_min = orig._min;
	_max = orig._max;

	return *this;
}
