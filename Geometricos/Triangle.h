/* 
 * File:   Triangle.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 13:57
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Vect2d.h"

class Triangle
{
	Vect2d a, b, c;

public:
	friend class DrawTriangle; //evitar

	/**
	 * @brief Constructor  
	 * @param aa vertex
	 * @param bb vertex 
	 * @param cc vertex
	 */
	Triangle(Vect2d& aa, Vect2d& bb, Vect2d& cc);

	/**
	 * @brief Copy constructor
	 * @param t
	 */

	Triangle(const Triangle& t);

	/**
	 * @brief getters 
	 * @return vertex A 
	 */

	Vect2d getA() { return a; }

	/**
	 * @brief getters 
	 * @return vertex A 
	 */
	Vect2d getB() { return b; }

	/**
	 * @brief getters 
	 * @return vertex A 
	 */
	Vect2d getC() { return c; }
};


#endif /* TRIANGLE_H */
