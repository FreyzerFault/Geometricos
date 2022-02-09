
#include <iostream>
#include "RayLine.h"
#include "Line.h"


RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b)
{
}

RayLine::RayLine(const RayLine& ray)
	: SegmentLine(ray)
{
}

RayLine::~RayLine()
{
}


RayLine & RayLine::operator=(const RayLine & rayline)
{
	if (this != &rayline)
	{
		SegmentLine::operator=(rayline);
	}

	return *this;
}

void RayLine::out()
{
	std::cout<< "RayLine: ";
	SegmentLine::out();
}