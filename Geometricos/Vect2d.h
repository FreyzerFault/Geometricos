
/* 
 * File:   Vect2d.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 14:01
 */

#ifndef VECT2D_H
#define VECT2D_H

#include "Point.h"


class Vect2d : public Point  {
    //double x, y;

public:    
    
    Vect2d () : Point () {};
    Vect2d (double x, double y): Point (x,y) {}
    
   
    double getX() {return _x; }
    double getY() {return _y; }
    
    /**
	*	@brief Copy constructor.
	*/
	Vect2d(const Vect2d& vector);

	/**
	*	@brief Copy constructor.
	*/
	Vect2d(const Point& point);

	/**
	*	@brief Destructor.
	*/
	virtual ~Vect2d();

	/**
	*	@brief Returns this + b (sum of vectors).
	*/
	Vect2d add(Vect2d& b);
        //Vect2d operator+ (const Vect2d &b);

	/**
	*	@brief Returns a . b (scalar product).
	*/
	double dot(Vect2d& b);

	/**
	*	@brief Assignment operator.
	*/
	virtual Vect2d& operator=(const Vect2d& vector);

	/**
	*	@brief Returns t . a (vector product by _a scalar).
	*/
	Vect2d scalarMult(double t);

	/**
	*	@brief Returns a - b (substraction of vectors).
	*/
	Vect2d sub(Vect2d& b);
};



#endif /* VECT2D_H */

