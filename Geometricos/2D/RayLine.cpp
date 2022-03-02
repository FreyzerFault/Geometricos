
#include <iostream>
#include "RayLine.h"
#include "Line.h"
#include "Vec2D.h"


GEO::RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b)
{
}

double GEO::RayLine::distPoint(const Point& point) const
{
	const double t0 = getDistanceT0(point);

	if (t0 <= 0)
		return Vec2D(point - _orig).getModule();

	const Vec2D d(_orig, _dest);
	
	return Vec2D(point - (_orig + (d * t0))).getModule();
}

bool GEO::RayLine::segmentIntersection(const SegmentLine& segment) const
{
	const Point a = _orig;
	// El b que este en cuenca
	const Point b = _orig + Vec2D(_orig, _dest) * 1000.0;

	const Point c = segment.getA();
	const Point d = segment.getB();

	// Siempre que no sea colineal para evitar falsos V / F
	// (b da igual)
	if (a.colinear(c,d) || c.colinear(a,b) || d.colinear(a,b))
		return false;

	// Con el XOR, Uno de los puntos del segmento debe estar a la izquierda
	return (a.left(c,d) ^ b.left(c,d) && c.left(a,b) ^ d.left(a,b));
}

bool GEO::RayLine::impSegmentIntersection(const SegmentLine& segment) const
{
	const Point a = _orig;
	const Point b = _dest;
	const Point c = segment.getA();
	const Point d = segment.getB();

	// Si son colineales
	return a.isBetween(c,d) // El inicio del ray esta en el segmento
	// El rayo pasa por c o por d, por lo que deben estar en medio o delante de a,b
	|| c.isBetween(a,b) || d.isBetween(a,b)
	|| c.forward(a,b) || d.forward(a,b);
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