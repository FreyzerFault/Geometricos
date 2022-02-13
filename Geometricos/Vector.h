﻿#pragma once
#include "BasicGeom.h"
#include "Point.h"

namespace GEO
{
	class Vector : public Point
	{
	public:
		Vector() : Point() {}

		Vector(double x, double y, bool polar = false) : Point(x,y, polar) {}
		Vector(Point& p0, Point& p1) : Vector(p1.getX() - p0.getX(), p1.getY() - p0.getY()) {}

		Vector add(Vector& v) const { return *this + v;}
		Vector sub(Vector& v) const { return *this - v;}

		double dot(Vector& v) const { return (_x * v.getX()) + (_y * v.getY());}
		Vector scalarMult(const double& s) const { return {_x * s, _y * s};}

		
		Vector operator+(Vector& p) const { return { _x - p.getX(), _y - p.getY() }; }
		Vector operator-(Vector& p) const { return { _x - p.getX(), _y - p.getY() }; }

		// Compara Modulos
		bool operator>(Point& p) const { return this->getModule() > p.getModule(); }
		bool operator<(Point& p) const { return this->getModule() < p.getModule(); }
		bool operator==(Point& p) const { return BasicGeom::equal(getModule(), p.getModule()); }
		bool operator<=(Point& p) const { return BasicGeom::lequal(getModule(), p.getModule()); }
		bool operator>=(Point& p) const { return BasicGeom::gequal(getModule(), p.getModule()); }
	};
}
