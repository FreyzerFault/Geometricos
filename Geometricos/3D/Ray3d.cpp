
#include <iostream>
#include "Edge3d.h"
#include "Ray3d.h"


GEO::Ray3d::Ray3d(Vec3D & orig, Vec3D & dest)
	: Edge3d(orig, dest)
{
}

GEO::Ray3d::Ray3d(const Ray3d & ray)
	: Edge3d(ray)
{
}

GEO::Ray3d::~Ray3d()
{
}

GEO::Ray3d & GEO::Ray3d::operator=(const Ray3d & ray)
{
	if (this != &ray)
	{
		Edge3d::operator=(ray);
	}

	return *this;
}

void GEO::Ray3d::out()
{
	std::cout << "Ray->Origin: ";
	_orig.out();
	std::cout << "Ray->Destination: ";
	_dest.out();
}