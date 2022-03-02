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

GEO::Point::Point(const Vec2D& v)
	: _x(v.getX()), _y(v.getY())
{
}


GEO::Point::PointClassification GEO::Point::classify(const Point& p0, const Point& p1) const
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
	const Vec2D a(p0, *this);
	const Vec2D b(p0, p1);

	if ((a.getX() * b.getX() < 0.0) || (a.getY() * b.getY() < 0.0))
		return PointClassification::BACKWARD;
	if (a > b)
		return PointClassification::FORWARD;

	return PointClassification::BETWEEN;
}

bool GEO::Point::leftAbove(const Point& a, const Point& b) const
{
	const PointClassification result = classify(a, b);
	return (result == PointClassification::LEFT) || (result != PointClassification::RIGHT);
}

bool GEO::Point::rightAbove(const Point& a, const Point& b) const
{
	const PointClassification result = classify(a, b);
	return (result == PointClassification::RIGHT) || (result != PointClassification::LEFT);
}

bool GEO::Point::colinear(const Point& a, const Point& b) const
{
	const PointClassification result = classify(a, b);
	return (result != PointClassification::LEFT) && (result != PointClassification::RIGHT);
}

double GEO::Point::distPoint(const Point& p) const
{
	return std::sqrt(std::pow(p._x - _x, 2) + std::pow(p._y - _y, 2));
}

bool GEO::Point::distinct(const Point& p) const
{
	return (abs(_x - p._x) > BasicGeom::EPSILON || std::abs(_y - p._y) > BasicGeom::EPSILON);
}

bool GEO::Point::equal(const Point& pt) const
{
	return (BasicGeom::equal(_x, pt._x) && BasicGeom::equal(_y, pt._y));
}

double GEO::Point::getAlpha() const
{
	return glm::acos(_x);
}


double GEO::Point::getModule() const
{
	return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
}


double GEO::Point::slope(const Point& p) const
{
	// Si es vertical
	if (BasicGeom::equal(BasicGeom::EPSILON, p.getX() - _x))
	{
		if (_y < p.getY())
			return BasicGeom::INFINITO;

		return BasicGeom::menosINFINITO; // Arriba-Abajo
	}

	return (p.getY() - _y) / (p.getX() - _x);
}

double GEO::Point::triangleArea2(const Point& a, const Point& b) const
{
	return BasicGeom::determinant3x3(
		a.getX(), a.getY(), 1,
		b.getX(), b.getY(), 1,
		_x, _y, 1
	);
}

GEO::Point GEO::Point::operator+(const Vec2D& v) const
{
	return {_x + v.getX(), _y + v.getY()};
}

GEO::Point GEO::Point::operator-(const Vec2D& v) const
{
	return {_x - v.getX(), _y - v.getY()};
}

GEO::Vec2D GEO::Point::operator-(const Point& v) const
{
	return {_x - v.getX(), _y - v.getY()};
}


void GEO::Point::out() const
{
	cout << toString() << endl;
}

string GEO::Point::toString() const
{
	return "( " + std::to_string(_x) + ", " + std::to_string(_y) + " )";
}
