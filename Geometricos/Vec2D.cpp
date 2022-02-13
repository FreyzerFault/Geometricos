#include "Vec2D.h"


GEO::Vec2D::Vec2D(const Point& point)
	: Point(point)
{
}

GEO::Vec2D::Vec2D(const Vec2D& v)
	: Point(v._x, v._y)
{
}

GEO::Vec2D::~Vec2D()
{
}

GEO::Vec2D GEO::Vec2D::add(Vec2D& b)
{
    //XXXX
	return Vec2D();
}

double GEO::Vec2D::dot(Vec2D& b)
{
    //XXXX
	return 0;
}

GEO::Vec2D & GEO::Vec2D::operator=(const Vec2D & vector)
{
	Point::operator=(vector);

	return *this;
}

GEO::Vec2D GEO::Vec2D::scalarMult(double t)
{
    //XXXX
	return Vec2D();
}

GEO::Vec2D GEO::Vec2D::sub(Vec2D& b)
{
    //XXXX
	return Vec2D(); 
}
