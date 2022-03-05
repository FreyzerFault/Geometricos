#include <iostream>
#include <cmath>
#include <string>
#include "Vec3D.h"
#include "BasicGeom.h"
#include "Triangle3D.h"


GEO::Vec3D::Vec3D()
{
	this->setVert(DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE);
}

GEO::Vec3D::Vec3D(double x, double y, double z) : _value{x, y, z}
{
}

GEO::Vec3D::Vec3D(const Vec3D & vector)
{
	_value[X] = vector._value[X];
	_value[Y] = vector._value[Y];
	_value[Z] = vector._value[Z];
}

GEO::Vec3D GEO::Vec3D::add(Vec3D & b)
{
	return {getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ()};
}

bool GEO::Vec3D::collinear(Vec3D & a, Vec3D & b)
{
	// Area del Triangulo es 0
	Triangle3D tr (a, b, *this);

	return GEO::BasicGeom::equal(tr.area(), GEO::BasicGeom::EPSILON);
}

double GEO::Vec3D::distance(Vec3D & p)
{
	//XXXX
	return 0; 
}

double GEO::Vec3D::dot(Vec3D & v)
{
	return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}

std::vector<double> GEO::Vec3D::getVector()
{
	return std::vector<double> {getX(), getY(), getZ()};
}

double GEO::Vec3D::getX()
{
	return _value[X];
}

double GEO::Vec3D::getY()
{
	return _value[Y];
}

double GEO::Vec3D::getZ()
{
	return _value[Z];
}

double GEO::Vec3D::module()
{
	return sqrt(getX() * getX() + getY() * getY() + getZ() * getZ());
}

GEO::Vec3D& GEO::Vec3D::operator=(const Vec3D& vector)
{
	this->_value[X] = vector._value[X];
	this->_value[Y] = vector._value[Y];
	this->_value[Z] = vector._value[Z];

	return *this;
}

bool GEO::Vec3D::operator==(const Vec3D & vector)
{
	return BasicGeom::equal(getX(), vector._value[X]) && BasicGeom::equal(getY(), vector._value[Y]) && BasicGeom::equal(getZ(), vector._value[Z]);
}

bool GEO::Vec3D::operator!=(const Vec3D & vector)
{
	return !(this->operator==(vector));
}

GEO::Vec3D GEO::Vec3D::scalarMul(double value)
{
	return Vec3D(getX() * value, getY() * value, getZ() * value);
}

void GEO::Vec3D::setX(double x)
{
	this->_value[X] = x;
}

void GEO::Vec3D::setY(double y)
{
	this->_value[Y] = y;
}

void GEO::Vec3D::setZ(double z)
{
	this->_value[Z] = z;
}

void GEO::Vec3D::setVert(double x, double y, double z)
{
	this->_value[X] = x;
	this->_value[Y] = y;
	this->_value[Z] = z;
}

GEO::Vec3D GEO::Vec3D::sub(Vec3D & b)
{
	return Vec3D(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ());
}

GEO::Vec3D GEO::Vec3D::cross(Vec3D & b)
{
	return Vec3D(getY() * b.getZ() - getZ() * b.getY(), getZ() * b.getX() - getX() * b.getZ(), getX() * b.getY() - getY() * b.getX());
}

void GEO::Vec3D::out()
{
	std::cout << "Coordinate x: " << std::to_string(getX()) << ", Coordinate y: " ;
		std::cout << std::to_string(getY()) << ", Coordinate z: " << std::to_string(getZ());
}
