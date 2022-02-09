
#include <iostream>
#include "Line.h"
#include "RayLine.h"
#include "SegmentLine.h"


Line::Line(const Point & a, const Point & b)
	: SegmentLine(a, b)
{
}

Line::Line(const Line & s)
	: SegmentLine(s)
{
}

Line::~Line()
{
}



Line & Line::operator=(const Line & line)
{
	if (this != &line)
	{
		SegmentLine::operator=(line);
	}

	return *this;
}


void Line::out()
{
	std::cout << "Line: ";
	std::cout << "Point A: ";
	this->_orig.out();
	std::cout << "Point B: ";
	this->_dest.out();
}
