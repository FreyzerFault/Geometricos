#include <cmath>
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "Point.h"
#include "Vec2D.h"

using namespace std;

std::string GEO::Point::classifyToString(PointClassification c)
{
	switch (c)
	{
	case PointClassification::LEFT:
		return "LEFT";
	case PointClassification::RIGHT:
		return "RIGHT";
	case PointClassification::FORWARD:
		return "FORWARD";
	case PointClassification::BACKWARD:
		return "BACKWARD";
	case PointClassification::BETWEEN:
		return "BETWEEN";
	case PointClassification::ORIGIN:
		return "ORIGIN";
	case PointClassification::DEST:
		return "DEST";
	}
	return "?";
}

GEO::Point::Point()
{
	_x = DEFAULT_VALUE;
	_y = DEFAULT_VALUE;
}

GEO::Point::Point(double x, double y, bool polar)
{
	if (!polar)
	{
		_x = x;
		_y = y;
	}
	else
	{
		_x = y * cos(x);
		_y = y * sin(x);
	}
}

GEO::Point::Point(Vec2D v)
	: _x(v.getX()), _y(v.getY())
{
}

GEO::Point::Point(const Point& point)
{
	_x = point._x;
	_y = point._y;
}

GEO::Point::~Point()
= default;

GEO::Point::PointClassification GEO::Point::classify(Point& p0, Point& p1)
{
	if (equal(p0))
		return PointClassification::ORIGIN;
	if (equal(p1))
		return PointClassification::DEST;

	const double areaTri = triangleArea2(p0, p1) / 2;

	if (areaTri > 0)
		return PointClassification::LEFT;
	if (areaTri < 0)
		return PointClassification::RIGHT;

	// Si Area = 0 Esta contenido en la recta
	// Para que este detras, el vector p0->this debe ser inverso al vector p0->p1
	Vec2D a(p0, *this);
	Vec2D b(p0, p1);

	if ((a.getX() * b.getX() < 0.0) || (a.getY() * b.getY() < 0.0))
		return PointClassification::BACKWARD;
	if (a > b)
		return PointClassification::FORWARD;

	return PointClassification::BETWEEN;
}

bool GEO::Point::colinear(Point& a, Point& b)
{
	const PointClassification result = classify(a, b);
	return (result != PointClassification::LEFT) && (result != PointClassification::RIGHT);
}

double GEO::Point::distPoint(Point& p) const
{
	return std::sqrt(std::pow(p._x - _x, 2) + std::pow(p._y - _y, 2));
}

double GEO::Point::getAlpha() const
{
	return glm::acos(_x);
}


double GEO::Point::getModule() const
{
	return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
}

bool GEO::Point::leftAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::LEFT) || (result != PointClassification::RIGHT);
}

GEO::Point& GEO::Point::operator=(const Point& point)
{
	_x = point._x;
	_y = point._y;

	return *this;
}

bool GEO::Point::rightAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::RIGHT) || (result != PointClassification::LEFT);
}

double GEO::Point::slope(Point& p)
{
	//XXXXX

	return 0;
}

double GEO::Point::triangleArea2(Point& a, Point& b) const
{
	return BasicGeom::determinant3x3(
		a.getX(), a.getY(), 1,
		b.getX(), b.getY(), 1,
		_x,			_y,	1
	);
}

GEO::Point GEO::Point::operator+(Vec2D v) const
{
	return {_x + v.getX(), _y + v.getY()};
}

GEO::Vec2D GEO::Point::operator-(Point v) const
{
	return {_x - v.getX(), _y - v.getY()};
}

GEO::Vec2D GEO::Point::operator*(double s)
{
	return Vec2D(*this) * s;
}

void GEO::Point::out() const
{
	string outstring = "Coordinate x: " + std::to_string(_x) + ", coordinate y: " + std::to_string(_y);
	cout << outstring << endl;
}
