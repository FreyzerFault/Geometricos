
/* 
 * File:   Vect2d.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:01
 */

#ifndef VECT2D_H
#define VECT2D_H

#include "Point.h"


namespace GEO
{
	class Vec2D : public Point {
		//double x, y;

	public:

		Vec2D() : Point() {};
		Vec2D(double x, double y) : Point(x, y) {}


		double getX() { return _x; }
		double getY() { return _y; }

		/**
		*	@brief Copy constructor.
		*/
		Vec2D(const Vec2D& vector);

		/**
		*	@brief Copy constructor.
		*/
		Vec2D(const Point& point);

		/**
		*	@brief Destructor.
		*/
		virtual ~Vec2D();

		/**
		*	@brief Returns this + b (sum of vectors).
		*/
		Vec2D add(Vec2D& b);
		//Vect2d operator+ (const Vect2d &b);

	/**
	*	@brief Returns a . b (scalar product).
	*/
		double dot(Vec2D& b);

		/**
		*	@brief Assignment operator.
		*/
		virtual Vec2D& operator=(const Vec2D& vector);

		/**
		*	@brief Returns t . a (vector product by _a scalar).
		*/
		Vec2D scalarMult(double t);

		/**
		*	@brief Returns a - b (substraction of vectors).
		*/
		Vec2D sub(Vec2D& b);
	};
}



#endif /* VECT2D_H */

