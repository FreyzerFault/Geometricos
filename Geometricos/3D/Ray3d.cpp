
#include <iostream>
#include "Edge3D.h"
#include "Ray3D.h"


GEO::Ray3D::Ray3D(const Vec3D& orig, const Vec3D& dest)
	: Edge3D(orig, dest)
{
}

GEO::Ray3D & GEO::Ray3D::operator=(const Ray3D & ray)
{
	if (this != &ray)
	{
		Edge3D::operator=(ray);
	}

	return *this;
}

void GEO::Ray3D::out()
{
	std::cout << "Ray->Origin: ";
	_orig.out();
	std::cout << "Ray->Destination: ";
	_dest.out();
}