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
		Vec2D(Point& p0, Point& p1) : Vec2D(p1.getX() - p0.getX(), p1.getY() - p0.getY()) {}
		Vec2D(Point& p) : Vec2D(p.getX(), p.getY()) {}

		Vec2D(const Vec2D& orig) : Vec2D(orig._x, orig._y) {}

		Vec2D add(Vec2D& v) const { return *this + v;}
		Vec2D sub(Vec2D& v) const { return *this - v;}

		double dot(Vec2D& v) const { return *this * v;}
		Vec2D scalarMult(const double s) const { return *this * s;}

		
		Vec2D operator+(Vec2D& p) const { return { _x - p.getX(), _y - p.getY() }; }
		Vec2D operator-(Vec2D& p) const { return { _x - p.getX(), _y - p.getY() }; }
		Vec2D operator*(const double s) const { return { _x * s, _y * s }; }
		double operator*(Vec2D& v) const { return (_x * v.getX()) + (_y * v.getY()); }

		// Compara Modulos
		bool operator>(Point& p) const { return this->getModule() > p.getModule(); }
		bool operator<(Point& p) const { return this->getModule() < p.getModule(); }
		bool operator==(Point& p) const { return BasicGeom::equal(getModule(), p.getModule()); }
		bool operator<=(Point& p) const { return BasicGeom::lequal(getModule(), p.getModule()); }
		bool operator>=(Point& p) const { return BasicGeom::gequal(getModule(), p.getModule()); }
	};
}
