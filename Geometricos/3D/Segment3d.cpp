
#include <iostream>
#include "Segment3d.h"


GEO::Segment3d::Segment3d(Vec3D & orig, Vec3D & dest)
	: Edge3d(orig, dest)
{
}

GEO::Segment3d::Segment3d(const Segment3d & segment)
	: Edge3d(segment)
{
}

GEO::Segment3d::~Segment3d()
{
}

GEO::Segment3d & GEO::Segment3d::operator=(const Segment3d & segment)
{
	if (this != &segment)
	{
		GEO::Edge3d::operator=(segment);
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