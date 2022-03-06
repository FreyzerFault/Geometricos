
#include <iostream>
#include "Segment3d.h"


GEO::Segment3d::Segment3d(const Vec3D& orig, const Vec3D& dest)
	: Edge3D(orig, dest)
{
}

GEO::Segment3d & GEO::Segment3d::operator=(const Segment3d & segment)
{
	if (this != &segment)
	{
		GEO::Edge3D::operator=(segment);
	}

	return *this;
}

void GEO::Segment3d::out()
{
	std::cout << "Segment->Origin: ";
	_orig.out();
	std::cout << "Segment->Destination: ";
	_dest.out();
}