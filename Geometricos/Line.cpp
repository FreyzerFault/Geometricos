
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

GEO::Line::Line(const Line & s)
	: SegmentLine(s)
{
}

GEO::Line::~Line()
= default;

double GEO::Line::distPoint(const Point& point) const
{
	const double t0 = getDistanceT0(point);
	
	const Vec2D d(_orig, _dest);
	
	return Vec2D(point - (_orig + (d * t0))).getModule();
}

bool GEO::Line::impSegmentIntersection(const SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment.getA();
	Point d = segment.getB();

	// Si son colineales
	return c.colinear(a,b) || d.colinear(a,b);
}

bool GEO::Line::segmentIntersection(const SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment.getA();
	Point d = segment.getB();

	// Cada punto del segmento debe estar a izquierda o derecha de a-b o 
	return ((c.right(a,b) && d.left(a,b)) || (c.right(b,a) && d.left(b,a)));
}

GEO::Point* GEO::Line::intersectionPoint(const SegmentLine& segment)
{
	double s, t;
	Point* interseccion = SegmentLine::intersectionPoint(segment.getA(), segment.getB(), s, t);

	// Esta dentro del segmento
	if (this->isTvalid(s) && segment.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::Line::intersectionPoint(const RayLine& ray)
{
	double s, t;
	Point* interseccion = SegmentLine::intersectionPoint(ray.getA(), ray.getB(), s, t);

	// Esta dentro del rayo
	if (this->isTvalid(s) && ray.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::Line::intersectionPoint(const Line& line)
{
	double s, t;
	Point* interseccion = SegmentLine::intersectionPoint(line.getA(), line.getB(), s, t);

	// Redundante
	if (this->isTvalid(s) && line.isTvalid(t))
		return interseccion;
	
	return nullptr;
}


GEO::Line& GEO::Line::operator=(const Line & line)
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
