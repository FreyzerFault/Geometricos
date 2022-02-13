#include <cmath>
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "Point.h"
#include "SegmentLine.h"

using namespace std;

Point::Point()
{
	_x = DEFAULT_VALUE;
	_y = DEFAULT_VALUE;
}

Point::Point(double x, double y, bool polar)
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

Point::Point(const Point& point)
{
	_x = point._x;
	_y = point._y;
}

Point::~Point()
= default;

Point::PointClassification Point::classify(Point& p0, Point& p1)
{
	if (equal(p0))
		return ORIGIN;
	if (equal(p1))
		return DEST;

	const double areaTri = triangleArea2(p0, p1) / 2;

	if (areaTri > 0)
		return LEFT;
	if (areaTri < 0)
		return RIGHT;

	// Si Area = 0 Esta contenido en la recta
	// Para que este detras, el vector p0->this debe ser inverso al vector p0->p1
	Point a = *this - p0;
	Point b = p1 - p0;

	if ((a.getX() * b.getX() < 0.0) || (a.getY() * b.getY() < 0.0))
		return BACKWARD;
	if (a > b)
		return FORWARD;

	return BETWEEN;
}

bool Point::colinear(Point& a, Point& b)
{
	const PointClassification result = classify(a, b);
	return (result != LEFT) && (result != RIGHT);
}

double Point::distPoint(Point& p) const
{
	return std::sqrt(std::pow(p._x - _x, 2) + std::pow(p._y - _y, 2));
}

double Point::getAlpha() const
{
	return glm::acos(_x);
}


double Point::getModule() const
{
	return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
}

bool Point::leftAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == LEFT) || (result != RIGHT);
}

Point& Point::operator=(const Point& point)
{
	_x = point._x;
	_y = point._y;

	return *this;
}

bool Point::rightAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == RIGHT) || (result != LEFT);
}

double Point::slope(Point& p)
{
	//XXXXX

	return 0;
}

double Point::triangleArea2(Point& a, Point& b) const
{
	return GEO::determinant3x3(
		a.getX(), a.getY(), 1,
		b.getX(), b.getY(), 1,
		_x,			_y,	1
	);
}

void Point::out()
{
	string outstring = "Coordinate x: " + std::to_string(_x) + ", coordinate y: " + std::to_string(_y);
	cout << outstring << endl;
}
