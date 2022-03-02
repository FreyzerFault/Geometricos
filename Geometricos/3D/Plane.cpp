
#include <iostream>
#include "Plane.h"
#include "BasicGeom.h"


GEO::Plane::Plane(Vec3D & p, Vec3D & u, Vec3D & v, bool arePoints)
{
	if (!arePoints)			// Vectors: pi = p + u * lambda + v * mu 
	{			
		_a = p;
		_b = u.add(_a);
		_c = v.add(_a);
	}
	else 
	{						// 3 points in the plane.
		_a = p;
		_b = u;
		_c = v;
	}
}

GEO::Plane::Plane(const Plane & plane)
	: _a(plane._a), _b(plane._b), _c(plane._c)
{
}

GEO::Plane::~Plane()
{
}

bool GEO::Plane::coplanar(Vec3D & point)
{
	
	//XXXX
	return false;
}

double GEO::Plane::distance(Vec3D & point)
{
	//XXXX
	
	return 0; 
}    

double GEO::Plane::getA()
{
	return (BasicGeom::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
}

double GEO::Plane::getB()
{
	return (BasicGeom::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));
}

double GEO::Plane::getC()
{
	return (BasicGeom::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
}

GEO::Vec3D GEO::Plane::getNormal()
{
	//XXXX
	
	return Vec3D();
}


bool GEO::Plane::intersect(Plane & plane, Line3d & line)
{
	//XXXX
	return true;
}

bool GEO::Plane::intersect(Line3d & line, Vec3D & point)
{
	
	//XXXX
	return true;
}

bool intersect(GEO::Plane& pa, GEO::Plane& pb, GEO::Vec3D& pinter){

//XXXX
	return true;
	
}

GEO::Plane & GEO::Plane::operator=(const Plane & plane)
{
	if (this != &plane)
	{
		_a = plane._a;
		_b = plane._b;
		_c = plane._c;
	}

	return *this;
}

void GEO::Plane::out()
{
	std::cout << "Plane->a: ";
	_a.out();
	std::cout <<"Plane->b: ";
	_b.out();
	std::cout <<"Plane->c: ";
	_c.out();
}