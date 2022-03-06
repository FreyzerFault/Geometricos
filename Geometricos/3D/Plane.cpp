
#include <iostream>
#include "Plane.h"
#include "BasicGeom.h"


GEO::Plane::Plane(Vec3D& p, Vec3D& u, Vec3D& v, bool arePoints)
	: _a(p), _b(arePoints ? u : (u + p)), _c(arePoints ? v : (v + p))
{
}

bool GEO::Plane::coplanar(Vec3D & p)
{
	
	//XXXX
	return false;
}

double GEO::Plane::distance(Vec3D & p)
{
	//XXXX
	
	return 0; 
}    

double GEO::Plane::getA() const
{
	return (BasicGeom::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getY() - _a.getY(), _b.getZ() - _a.getZ()));
}

double GEO::Plane::getB() const
{
	return (BasicGeom::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getZ() - _a.getZ(), _b.getX() - _a.getX()));
}

double GEO::Plane::getC() const
{
	return (BasicGeom::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getX() - _a.getX(), _b.getY() - _a.getY()));
}

double GEO::Plane::getD() const
{
	return (-1.0) * (getA() * _a.getX() + getB() * _a.getY() + getC() * _a.getZ());
}

GEO::Vec3D GEO::Plane::getNormal()
{
	//XXXX
	
	return Vec3D();
}


bool GEO::Plane::intersect(Plane & plane, Line3D & line)
{
	//XXXX
	return true;
}

bool GEO::Plane::intersect(Plane& pa, Plane& pb, Vec3D& pinter)
{
	//XXXX
	return true;
}

bool GEO::Plane::intersect(Line3D & line, Vec3D & point)
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