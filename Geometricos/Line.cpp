
#include <iostream>
#include "Line.h"
#include "RayLine.h"
#include "SegmentLine.h"

GEO::Line::Line(const GEO::Point & a, const GEO::Point & b)
	: SegmentLine(a, b)
{
}

GEO::Line::Line(const Line & s)
	: SegmentLine(s)
{
}

GEO::Line::~Line()
{
}



GEO::Line & GEO::Line::operator=(const Line & line)
{
	if (this != &line)
	{
		GEO::SegmentLine::operator=(line);
	}

	return *this;
}


void GEO::Line::out()
{
	std::cout << "Line: ";
	std::cout << "Point A: ";
	this->_orig.out();
	std::cout << "Point B: ";
	this->_dest.out();
}
