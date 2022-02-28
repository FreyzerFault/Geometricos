// ReSharper disable CppHidingFunction
#pragma once
#include "BasicGeom.h"
#include "Point.h"

namespace GEO
{
	class Vec2D : public Point
	{
	public:
		Vec2D() : Point() {}

		Vec2D(double x, double y, bool polar = false) : Point(x,y, polar) {}
		Vec2D(const Point& p0, const Point& p1) : Vec2D(p1.getX() - p0.getX(), p1.getY() - p0.getY()) {}
		Vec2D(const Point& p) : Vec2D(p.getX(), p.getY()) {}

		Vec2D(const Vec2D& orig) : Vec2D(orig._x, orig._y) {}

		Vec2D add(const Vec2D& v) const { return *this + v;}
		Vec2D sub(const Vec2D& v) const { return *this - v;}

		double dot(const Vec2D& v) const { return *this * v;}
		Vec2D scalarMult(const double s) const { return *this * s;}

		Vec2D getPerpendicular() { return {_y, -_x}; }
		
		Vec2D operator+(const Vec2D& p) const { return { _x + p.getX(), _y + p.getY() }; }
		Vec2D operator-(const Vec2D& p) const { return { _x - p.getX(), _y - p.getY() }; }
		Vec2D operator*(const double s) const { return { _x * s, _y * s }; }
		double operator*(const Vec2D& v) const { return (_x * v.getX()) + (_y * v.getY()); }

		// Compara Modulos
		bool operator>(const Point& p) const { return this->getModule() > p.getModule(); }
		bool operator<(const Point& p) const { return this->getModule() < p.getModule(); }
		bool operator==(const Point& p) const { return BasicGeom::equal(getModule(), p.getModule()); }
		bool operator<=(const Point& p) const { return BasicGeom::lequal(getModule(), p.getModule()); }
		bool operator>=(const Point& p) const { return BasicGeom::gequal(getModule(), p.getModule()); }
	};
}
