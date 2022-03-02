
#include <iostream>
#include <cmath>
#include "BasicGeom.h"
#include "Triangle3D.h"
#include "Edge3d.h"


GEO::Triangle3D::Triangle3D()
{
}

GEO::Triangle3D::Triangle3D(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
	: _a(ax, ay, az), _b(bx, by, bz), _c(cx, cy, cz)
{
}

GEO::Triangle3D::Triangle3D(const Triangle3D & triangle)
	: _a(triangle._a), _b(triangle._b), _c(triangle._c)
{
}

GEO::Triangle3D::Triangle3D(Vec3D & va, Vec3D & vb, Vec3D & vc)
	: _a(va), _b(vb), _c(vc)
{
}

GEO::Triangle3D::~Triangle3D()
{
}

double GEO::Triangle3D::area()
{
	//XXXX
	
	return 0; 
		
}

GEO::Triangle3D::PointPosition GEO::Triangle3D::classify(Vec3D & point)
{
	//XXXX

	return PointPosition::COPLANAR;
}


GEO::Vec3D GEO::Triangle3D::normal()
{
	Vec3D v1 (_b.sub(_a));
	Vec3D v2 (_c.sub(_a));
	Vec3D n (v1.xProduct(v2));
	double module = n.module();

	return (n.scalarMul(1.0f / module));
}

GEO::Triangle3D & GEO::Triangle3D::operator=(const Triangle3D & triangle)
{
	_a = triangle._a;
	_b = triangle._b;
	_c = triangle._c;

	return *this;
}

void GEO::Triangle3D::out()
{
	std::cout << "Triangle 3D: ";
	_a.out();
	_b.out();
	_c.out();
}



void GEO::Triangle3D::set(Vec3D & va, Vec3D & vb, Vec3D & vc)
{
	_a = va;
	_b = vb;
	_c = vc;
}

