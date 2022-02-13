#include <cmath>
#include <iostream>
#include "SegmentLine.h"
#include "RayLine.h"
#include "Vector.h"


GEO::SegmentLine::SegmentLine()
{
}

GEO::SegmentLine::SegmentLine(const Point& a, const Point& b)
	: _orig(a), _dest(b)
{
}

GEO::SegmentLine::SegmentLine(const SegmentLine& segment)
	: _orig(segment._orig), _dest(segment._dest)
{
}

GEO::SegmentLine::SegmentLine(double ax, double ay, double bx, double by)
	: _orig(ax, ay), _dest(bx, by)
{
}

GEO::SegmentLine::~SegmentLine()
{
}


GEO::SegmentLine & GEO::SegmentLine::operator=(const SegmentLine & segment)
{
	if (this != &segment)
	{
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}


double GEO::SegmentLine::getEquC()
{
	// c = y-mx (Si m = INF --> y-INF)
	if (isVertical())
		return BasicGeom::menosINFINITO;

	return _orig.getY() - (slope() * _orig.getX());
}

bool GEO::SegmentLine::distinct(SegmentLine & segment)
{
	return !equal(segment);
}



bool GEO::SegmentLine::equal(SegmentLine & segment) const
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

GEO::Point GEO::SegmentLine::getPoint(double t)
{
	// a + t(b-a)
	return {_orig + Vector(_orig, _dest) * t};
}



bool GEO::SegmentLine::isHorizontal()
{
	// Puntos a la misma Y
	return BasicGeom::equal(_orig.getY(), _dest.getY());
}




bool GEO::SegmentLine::isVertical()
{
	// Puntos a la misma X
	return BasicGeom::equal(_orig.getX(), _dest.getX());
}


double GEO::SegmentLine::slope()
{
	// (yb - ya) / (xb - xa)
	double x = _dest.getX() - _orig.getX();
	double y = _dest.getX() - _orig.getX();

	if (BasicGeom::equal(x, BasicGeom::CERO))
		return BasicGeom::INFINITO;

	return x / y;
}


bool GEO::SegmentLine::segmentIntersection(const SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment._orig;
	Point d = segment._dest;

	// Cada punto del segmento izquierda y derecha de los del otro segmento
	// en cualquier orden a-b o b-a
	return ((a.left(c,d) && b.right(c,d)) || (a.left(d,c) && b.right(d,c))
		&& (c.left(a,b) && d.right(a,b)) || (c.left(b,a) && d.right(b,a)));
}

bool GEO::SegmentLine::impSegmentIntersection(const SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment._orig;
	Point d = segment._dest;

	// Si algun punto esta entre los puntos del otro segmento
	return a.isBetween(c,d) || b.isBetween(c,d) || c.isBetween(a,b) || d.isBetween(a,b);
}



 // PROTECTED METHODS



void GEO::SegmentLine::out()
{
	std::cout << "Point A: )";
	_orig.out();
	std::cout << "Point B: ";
	_dest.out();
}




