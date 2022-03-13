
#include <iostream>
#include "Segment3D.h"


GEO::Segment3D::Segment3D(const Vec3D& orig, const Vec3D& dest)
	: Edge3D(orig, dest)
{
}

GEO::Segment3D & GEO::Segment3D::operator=(const Segment3D & segment)
{
	if (this != &segment)
	{
		GEO::Edge3D::operator=(segment);
	}

	return *this;
}

void GEO::Segment3D::out()
{
	std::cout << "Segment->Origin: ";
	_orig.out();
	std::cout << "Segment->Destination: ";
	_dest.out();
}