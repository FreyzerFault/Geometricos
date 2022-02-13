
#include <iostream>
#include "RayLine.h"
#include "Line.h"


GEO::RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b)
{
}

GEO::RayLine::RayLine(const RayLine& ray)
	: SegmentLine(ray)
{
}

GEO::RayLine::~RayLine()
{
}


GEO::RayLine & GEO::RayLine::operator=(const RayLine & rayline)
{
	if (this != &rayline)
	{
		SegmentLine::operator=(rayline);
	}

	return *this;
}

void GEO::RayLine::out()
{
	std::cout<< "RayLine: ";
	SegmentLine::out();
}