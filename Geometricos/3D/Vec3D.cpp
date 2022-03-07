#include <iostream>
#include <cmath>
#include <string>
#include "Vec3D.h"
#include "BasicGeom.h"
#include "Triangle3D.h"


GEO::Vec3D::Vec3D()
{
	this->setVec(DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE);
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

GEO::Vec3D GEO::Vec3D::add(const Vec3D& b) const
{
	return {getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ()};
}

bool GEO::Vec3D::collinear(const Vec3D& a, const Vec3D& b) const
{
	// Area del Triangulo es 0
	const Triangle3D tr (a, b, *this);

	return BasicGeom::equal(tr.area(), BasicGeom::EPSILON);
}

double GEO::Vec3D::distance(const Vec3D & p) const
{
	return (*this - p).module();
}

double GEO::Vec3D::dot(const Vec3D & v) const
{
	return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}

std::vector<double> GEO::Vec3D::getVector() const
{
	return std::vector {getX(), getY(), getZ()};
}

double GEO::Vec3D::getX() const
{
	return _value[X];
}

double GEO::Vec3D::getY() const
{
	return _value[Y];
}

double GEO::Vec3D::getZ() const
{
	return _value[Z];
}

double GEO::Vec3D::module() const
{
	return sqrt(getX() * getX() + getY() * getY() + getZ() * getZ());
}

GEO::Vec3D GEO::Vec3D::normalize() const
{
	return *this / module();
}

GEO::Vec3D& GEO::Vec3D::operator=(const Vec3D& vector)
{
	this->_value[X] = vector._value[X];
	this->_value[Y] = vector._value[Y];
	this->_value[Z] = vector._value[Z];

	return *this;
}

bool GEO::Vec3D::operator==(const Vec3D & vector) const
{
	return BasicGeom::equal(getX(), vector._value[X]) && BasicGeom::equal(getY(), vector._value[Y]) && BasicGeom::equal(getZ(), vector._value[Z]);
}

bool GEO::Vec3D::operator!=(const Vec3D & vector) const
{
	return !(this->operator==(vector));
}

GEO::Vec3D GEO::Vec3D::operator+(const Vec3D& v) const
{
	return this->add(v);
}

GEO::Vec3D GEO::Vec3D::operator-(const Vec3D& v) const
{
	return this->sub(v);
}

GEO::Vec3D GEO::Vec3D::operator*(const double s) const
{
	return this->scalarMul(s);
}

GEO::Vec3D GEO::Vec3D::operator/(double s) const
{
	return *this * (1 / s);
}

GEO::Vec3D GEO::Vec3D::scalarMul(double value) const
{
	return {getX() * value, getY() * value, getZ() * value};
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

void GEO::Vec3D::setVec(double x, double y, double z)
{
	this->_value[X] = x;
	this->_value[Y] = y;
	this->_value[Z] = z;
}

GEO::Vec3D GEO::Vec3D::sub(const Vec3D & b) const
{
	return {getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ()};
}

GEO::Vec3D GEO::Vec3D::cross(const Vec3D & b) const
{
	return {
		getY() * b.getZ() - getZ() * b.getY(),
		getZ() * b.getX() - getX() * b.getZ(),
		getX() * b.getY() - getY() * b.getX()
	};
}

void GEO::Vec3D::out()
{
	std::cout << "Coordinate x: " << std::to_string(getX()) << ", Coordinate y: " ;
		std::cout << std::to_string(getY()) << ", Coordinate z: " << std::to_string(getZ());
}
