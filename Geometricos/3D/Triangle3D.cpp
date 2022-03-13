#include <iostream>
#include <cmath>
#include "BasicGeom.h"
#include "Triangle3D.h"
#include "Edge3D.h"


GEO::Triangle3D::Triangle3D(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
	: _a(ax, ay, az), _b(bx, by, bz), _c(cx, cy, cz)
{
}

GEO::Triangle3D::Triangle3D(const Vec3D& va, const Vec3D& vb, const Vec3D& vc)
	: _a(va), _b(vb), _c(vc)
{
}

double GEO::Triangle3D::area() const
{
	// La MITAD del Area del rectangulo que formaria
	return (_a - _b).module() * (_a - _c).module() / 2;
}

GEO::Triangle3D::PointPosition GEO::Triangle3D::classify(const Vec3D& point) const
{
	// Resolviendo la ecuacion del plano Ax + By + Cz + D = s
	const Plane plane(_a, _b, _c, true);
	const double s = plane.getA() * point.getX() + plane.getB() * point.getY() + plane.getC() * point.getZ() + plane.getD();

	// s determina el lado del punto

	if (s > BasicGeom::EPSILON)
		return POSITIVE;

	if (s < BasicGeom::EPSILON)
		return NEGATIVE;

	// Si s == 0
	return COPLANAR;
}


GEO::Vec3D GEO::Triangle3D::normal() const
{
	const Vec3D v1 (_b.sub(_a));
	const Vec3D v2 (_c.sub(_a));

	return v1.cross(v2).normalize();
}



void GEO::Triangle3D::set(const Vec3D& va, const Vec3D& vb, const Vec3D& vc)
{
	_a = va;
	_b = vb;
	_c = vc;
}

void GEO::Triangle3D::out()
{
	std::cout << "Triangle 3D: ";
	_a.out();
	_b.out();
	_c.out();
}

