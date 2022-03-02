#include <iostream>
#include "Line.h"
#include "RayLine.h"
#include "Vec2D.h"

GEO::Line::Line(const GEO::Point & a, const GEO::Point & b)
	: SegmentLine(a, b)
{
}

GEO::Line::Line(const Point& p, const Vec2D& v)
	: SegmentLine(p, p + v)
{
}

GEO::Line& GEO::Line::operator=(const Line & line)
{
	if (this != &line)
	{
		SegmentLine::operator=(line);
	}

	return *this;
}

double GEO::Line::distPoint(const Point& point) const
{
	const double t0 = getDistanceT0(point);
	
	const Vec2D d(_orig, _dest);
	
	return Vec2D(point - (_orig + (d * t0))).getModule();
}

bool GEO::Line::segmentIntersection(const SegmentLine& segment) const
{
	const Point a = _orig;
	const Point b = _dest;
	const Point c = segment.getA();
	const Point d = segment.getB();

	// Siempre que c este Izquierda y d Derecha o viceversa de a,b
	return c.left(a,b) ^ d.left(a,b);
}

bool GEO::Line::impSegmentIntersection(const SegmentLine& segment) const
{
	const Point a = _orig;
	const Point b = _dest;
	const Point c = segment.getA();
	const Point d = segment.getB();

	// Si son colineales
	return c.colinear(a,b) || d.colinear(a,b);
}





void GEO::Line::out()
{
	std::cout << "Line: ";
	std::cout << "Point A: ";
	this->_orig.out();
	std::cout << "Point B: ";
	this->_dest.out();
}
