
#include <iostream>
#include "Line.h"
#include "RayLine.h"

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

bool GEO::Line::impSegmentIntersection(SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment.getA();
	Point d = segment.getB();

	// Si son colineales
	return c.colinear(a,b) || d.colinear(a,b);
}

bool GEO::Line::segmentIntersection(SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment.getA();
	Point d = segment.getB();

	// Cada punto del segmento debe estar a izquierda o derecha de a-b o 
	return ((c.right(a,b) && d.left(a,b)) || (c.right(b,a) && d.left(b,a)));
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
