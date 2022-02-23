
#include <iostream>
#include "RayLine.h"
#include "Line.h"


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

bool GEO::RayLine::impSegmentIntersection(SegmentLine& segment) const
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