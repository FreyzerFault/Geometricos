#include <cmath>
#include <iostream>
#include "SegmentLine.h"
#include "RayLine.h"
#include "Line.h"
#include "Vec2D.h"


double GEO::SegmentLine::getDistanceT0(Point& point)
{
	// Contenido => 0
	if (point.isBetween(_orig, _dest))
		return 0;

	// Delante => Distancia respecto a b
	if (point.forward(_orig, _dest))
		return Vec2D((Point)point - _dest).getModule();

	// Detras => Distancia respecto a a
	if (point.backward(_orig, _dest))
		return Vec2D((Point)point - _orig).getModule();

	// Izquierda o Derecha => distancia por la normal
	Vec2D v = _dest - _orig;
	const Vec2D normal = v.getPerpendicular();

	// Recta formada por el punto y la normal
	const Line perpendicular(point, normal);

	// Donde intersecta es el punto mas cercano
	const Point* intersection = intersectionPoint(perpendicular);

	// Si intersecta es la distancia con la interseccion
	if (intersection)
		return Vec2D(*intersection - point).getModule();

	// Si no intersecta sera la distancia con el punto de orig o dest mas cercano
	const double d1 = Vec2D(point, _dest).getModule();
	const double d2 = Vec2D(point, _orig).getModule();
	return BasicGeom::min2(d1, d2);
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


double GEO::SegmentLine::getEquC()
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



bool GEO::SegmentLine::equal(SegmentLine & segment) const
{
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

GEO::Point GEO::SegmentLine::getPoint(double t)
{
	// a + t(b-a)
	return {_orig + Vec2D(_orig, _dest) * t};
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
	if (this->isTvalid(s) && segment.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::SegmentLine::intersectionPoint(const RayLine& ray)
{
	double s, t;
	Point* interseccion = intersectionPoint(ray._orig, ray._dest, s, t);

	// Esta dentro del segmento (s) y del rayo (t)
	if (this->isTvalid(s) && ray.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::SegmentLine::intersectionPoint(const Line& line)
{
	double s, t;
	Point* interseccion = intersectionPoint(line._orig, line._dest, s, t);

	// Esta dentro del segmento (s)
	if (this->isTvalid(s) && line.isTvalid(t))
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




