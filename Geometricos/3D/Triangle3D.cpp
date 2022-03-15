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
	const Plane plane = getPlane();
	const double s = plane.getA() * point.getX() + plane.getB() * point.getY() + plane.getC() * point.getZ() + plane.getD();

	// s determina el lado del punto

	if (s > BasicGeom::EPSILON)
		return POSITIVE;

	if (s < BasicGeom::EPSILON)
		return NEGATIVE;

	// Si s == 0
	return COPLANAR;
}

bool GEO::Triangle3D::rayIntersection(const Ray3D& ray, Vec3D& point) const
{
	const Vec3D v0 = _a;
	const Vec3D v1 = _b;
	const Vec3D v2 = _c;

	const Vec3D rayP = ray.getOrig();
	const Vec3D rayV = ray.getVector();

	const Vec3D edge1 = v1 - v0;
	const Vec3D edge2 = v2 - v0;

	const Vec3D h = rayV.cross(edge2);

	const double a = edge1.dot(h);

	// Rayo Paralelo al triangulo
	if (BasicGeom::equal(a, 0))
		return false;

	const double f = 1.0 / a;

	const Vec3D s = rayP - v0;

	const double u = f * s.dot(h);

	if (u < 0.0 || u > 1.0)
		return false;


	const Vec3D q = s.cross(edge1);

	const double v = f * rayV.dot(q);

	if (v < 0.0 || u + v > 1.0)
		return false;


	// Calculamos t
	const float t = f * edge2.dot(q);

	if (t > BasicGeom::EPSILON)
	{
		point = rayP + rayV * t;
		return true;
	}


	// Interseccion = Linea, NO un punto
	return false;
}


GEO::Vec3D GEO::Triangle3D::normal() const
{
	const Vec3D v1 (_b.sub(_a));
	const Vec3D v2 (_c.sub(_a));

	return v1.cross(v2).normalize();
}

GEO::Plane GEO::Triangle3D::getPlane() const
{
	return {_a, _b, _c, true};
}

GEO::Vec3D GEO::Triangle3D::getNormal() const
{
	return getPlane().getNormal();
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

