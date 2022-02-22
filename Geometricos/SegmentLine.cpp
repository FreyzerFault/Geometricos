#include <cmath>
#include <iostream>
#include "SegmentLine.h"
#include "RayLine.h"
#include "Line.h"
#include "Vec2D.h"


double GEO::SegmentLine::getDistanceT0(const Point& point) const
{
	const Vec2D d = _dest - _orig;

	// t0 es el % a la que esta el punto mas cerca a point
	return (d * (point - _orig)) / (d*d);
}

GEO::SegmentLine::SegmentLine()
= default;

GEO::SegmentLine::SegmentLine(const Point& a, const Point& b)
	: _orig(a), _dest(b)
{
}

GEO::SegmentLine::SegmentLine(const SegmentLine& segment)
= default;

GEO::SegmentLine::SegmentLine(double ax, double ay, double bx, double by)
	: _orig(ax, ay), _dest(bx, by)
{
}

GEO::SegmentLine::~SegmentLine()
= default;


GEO::SegmentLine & GEO::SegmentLine::operator=(const SegmentLine & segment)
{
	if (this != &segment)
	{
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}


double GEO::SegmentLine::getEquC() const
{
	// c = y-mx (Si m = INF --> y-INF)
	if (isVertical())
		return BasicGeom::menosINFINITO;

	return _orig.getY() - (slope() * _orig.getX());
}

bool GEO::SegmentLine::distinct(SegmentLine & segment) const
{
	return !equal(segment);
}

double GEO::SegmentLine::distPoint(const Point& point) const
{
	const double t0 = getDistanceT0(point);
	// Mas atras
	if (t0 <= BasicGeom::CERO)
		return Vec2D(point - _orig).getModule();

	const Vec2D d(_orig, _dest);

	// Mas adelante
	if (t0 >= 1)
		return  Vec2D(point -( _orig + d)).getModule();

	// Entre orig y dest
	return  Vec2D(point - (_orig + (d * t0))).getModule();
}


bool GEO::SegmentLine::equal(SegmentLine & segment) const
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

GEO::Point GEO::SegmentLine::getPoint(double t) const
{
	// a + t(b-a)
	const Vec2D a(_orig);
	const Vec2D b(_dest);
	return {a + ((b - a) * t)};
}



bool GEO::SegmentLine::isHorizontal() const
{
	// Puntos a la misma Y
	return BasicGeom::equal(_orig.getY(), _dest.getY());
}




bool GEO::SegmentLine::isVertical() const
{
	// Puntos a la misma X
	return BasicGeom::equal(_orig.getX(), _dest.getX());
}


double GEO::SegmentLine::slope() const
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

	// Siempre que no sea colineal para evitar falsos V / F
	if (a.colinear(c,d) || b.colinear(c,d) || c.colinear(a,b) || d.colinear(a,b))
		return false;

	// Con el XOR, Uno de los puntos del segmento debe estar a la izquierda
	return (a.left(c,d) ^ b.left(c,d) && c.left(a,b) ^ d.left(a,b));
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

GEO::Point* GEO::SegmentLine::intersectionPoint(Point c, Point d, double& s, double& t)
{
	Vec2D a = _orig;
	Vec2D b = _dest;

	Vec2D ab = b - a;
	Vec2D cd = d - c;
	Vec2D ac = c - a;

	const double denominador = cd.getX() * ab.getY() - ab.getX() * cd.getY();

	if (BasicGeom::equal(denominador, 0))
	{
		std::cout << "Los segmentos son paralelos, no hay punto de interseccion" << std::endl;
		return nullptr;
	}

	s = (cd.getX() * ac.getY() - ac.getX() * cd.getY()) / denominador;

	t = (ab.getX() * ac.getY() - ac.getX() * ab.getY()) / denominador;

	Point abInters = getPoint(s);
	Point cdInters = SegmentLine(c,d).getPoint(t);

	// Si son paralelos
	if (!abInters.equal(cdInters))
	{
		std::cout << "Los puntos en cada segmento NO CONCUERDAN WTF" << std::endl;
		return nullptr;
	}

	return new Point(abInters);
}

GEO::Point* GEO::SegmentLine::intersectionPoint(const SegmentLine& segment)
{
	double s, t;
	Point* interseccion = intersectionPoint(segment._orig, segment._dest, s, t);

	// Esta dentro de ambos segmentos
	if (s >= BasicGeom::CERO && s <= 1 && t >= BasicGeom::CERO && t <= 1)
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::SegmentLine::intersectionPoint(const RayLine& ray)
{
	double s, t;
	Point* interseccion = intersectionPoint(ray._orig, ray._dest, s, t);

	// Esta dentro del segmento (s) y del rayo (t)
	if (s >= BasicGeom::CERO && s <= 1 && t >= BasicGeom::CERO)
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::SegmentLine::intersectionPoint(const Line& line)
{
	double s, t;
	Point* interseccion = intersectionPoint(line._orig, line._dest, s, t);

	// Esta dentro del segmento (s)
	if (s >= BasicGeom::CERO && s <= 1)
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}


// PROTECTED METHODS



void GEO::SegmentLine::out()
{
	std::cout << "Point A: )";
	_orig.out();
	std::cout << "Point B: ";
	_dest.out();
}




