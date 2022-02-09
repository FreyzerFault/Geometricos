#include "Vect2d.h"


Vect2d::Vect2d(const Point& point)
	: Point(point)
{
}

Vect2d::Vect2d(const Vect2d& v)
	: Point(v._x, v._y)
{
}

Vect2d::~Vect2d()
{
}

Vect2d Vect2d::add(Vect2d& b)
{
    //XXXX
	return Vect2d();
}

double Vect2d::dot(Vect2d& b)
{
    //XXXX
	return 0;
}

Vect2d & Vect2d::operator=(const Vect2d & vector)
{
	Point::operator=(vector);

	return *this;
}

Vect2d Vect2d::scalarMult(double t)
{
    //XXXX
	return Vect2d();
}

Vect2d Vect2d::sub(Vect2d& b)
{
    //XXXX
	return Vect2d(); 
}
