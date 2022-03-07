
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
	return (_a - _b).module() * (_a - _c).module() / 2;
}

GEO::Triangle3D::PointPosition GEO::Triangle3D::classify(Vec3D & point)
{
	//TODO

	return COPLANAR;
}


GEO::Vec3D GEO::Triangle3D::normal() const
{
	const Vec3D v1 (_b.sub(_a));
	const Vec3D v2 (_c.sub(_a));

	return v1.cross(v2).normalize();
}



void GEO::Triangle3D::set(Vec3D & va, Vec3D & vb, Vec3D & vc)
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

