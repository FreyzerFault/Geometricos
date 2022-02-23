
#include <iostream>
#include "RayLine.h"
#include "Line.h"
#include "Vec2D.h"


GEO::RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b)
{
}

GEO::RayLine::RayLine(const RayLine& ray)
	: SegmentLine(ray)
{
}

GEO::RayLine::~RayLine()
= default;

double GEO::RayLine::distPoint(const Point& point) const
{
	const double t0 = getDistanceT0(point);

	if (t0 <= 0)
		return Vec2D(point - _orig).getModule();

	const Vec2D d(_orig, _dest);
	
	return Vec2D(point - (_orig + (d * t0))).getModule();
}

bool GEO::RayLine::impSegmentIntersection(const SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment.getA();
	Point d = segment.getB();

	// Si son colineales
	return c.isBetween(a,b) // El inicio del ray esta en el segmento
	// El rayo pasa por a o por b, por lo que deben estar en medio o delante de c,d
	|| a.isBetween(c,d) || b.isBetween(c,d)
	|| a.forward(c,d) || c.forward(c,d);
}

bool GEO::RayLine::segmentIntersection(const SegmentLine& segment) const
{
	Point a = _orig;
	Point b = _dest;
	Point c = segment.getA();
	// El d que este en cuenca
	Point d = segment.getA() + Vec2D(segment.getA(), segment.getB()) * 1000.0;

	// Siempre que no sea colineal para evitar falsos V / F
	// (d da igual)
	if (a.colinear(c,d) || b.colinear(c,d) || c.colinear(a,b))
		return false;

	// Con el XOR, Uno de los puntos del segmento debe estar a la izquierda
	return (a.left(c,d) ^ b.left(c,d) && c.left(a,b) ^ d.left(a,b));
}

GEO::Point* GEO::RayLine::intersectionPoint(const SegmentLine& segment)
{
	double s, t;
	Point* interseccion = SegmentLine::intersectionPoint(segment.getA(), segment.getB(), s, t);

	// Esta dentro del segmento y el rayo
	if (this->isTvalid(s) && segment.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::RayLine::intersectionPoint(const RayLine& ray)
{
	double s, t;
	Point* interseccion = SegmentLine::intersectionPoint(ray.getA(), ray.getB(), s, t);

	// Esta dentro de ambos rayos
	if (this->isTvalid(s) && ray.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
}

GEO::Point* GEO::RayLine::intersectionPoint(const Line& line)
{
	double s, t;
	Point* interseccion = SegmentLine::intersectionPoint(line.getA(), line.getB(), s, t);

	// Esta dentro del rayo
	if (this->isTvalid(s) && line.isTvalid(t))
		return interseccion;

	// En caso de que este contenido
	return nullptr;
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