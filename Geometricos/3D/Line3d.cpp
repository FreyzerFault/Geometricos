#include <iostream>
#include <climits>
#include <cmath>
#include "BasicGeom.h"
#include "Line3D.h"

GEO::Line3D::Line3D(const Vec3D& orig, const Vec3D& dest)
	: Edge3D(orig, dest)
{
}

double GEO::Line3D::distance(const Line3D & line) const
{
	const Vec3D p1 = _orig;
	const Vec3D p2 = line.getOrig();
	const Vec3D v1 = _dest - _orig;
	const Vec3D v2 = line.getDest() - line.getOrig();

	// Los planos paralelos que contienen a ambas lineas comparte una Perpendicular (v x v')
	const Vec3D perp = v1.cross(v2);
	// Para sacar la distancia entre planos cogemos cualquier vector de un plano a otro (p - p')
	// La proyeccion de ese vector arbitrario sobre el perpendicular es el vector distancia
	// perp · (p-p') / |perp|
	const double proyection = abs(perp.dot(p1 - p2));

	return proyection / perp.module();
}

GEO::Line3D GEO::Line3D::normalLine(Vec3D& p) const
{
	return {p, p + normal(p)};
}

GEO::Line3D & GEO::Line3D::operator=(const Line3D & line)
{
	if (this != &line)
	{
		Edge3D::operator=(line);
	}

	return *this;
}

void GEO::Line3D::out()
{
	std::cout << "Line->Origin: ";
	_orig.out();
	std::cout << "Line->Destination: ";
	_dest.out();
}

