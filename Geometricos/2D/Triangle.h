/* 
 * File:   Triangle.h
 * Author: lidia
 *
 * Created on 5 de enero de 2021, 13:57
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Vec2D.h"

namespace GEO
{
	class Triangle
	{
		Vec2D a, b, c;

	public:
		friend class DrawTriangle; //evitar

		/**
		 * @brief Constructor
		 * @param aa vertex
		 * @param bb vertex
		 * @param cc vertex
		 */
		Triangle(Vec2D& aa, Vec2D& bb, Vec2D& cc);

		/**
		 * @brief Copy constructor
		 * @param t
		 */

		Triangle(const Triangle& t);

		/**
		 * @brief getters
		 * @return vertex A
		 */

		Vec2D getA() { return a; }

		/**
		 * @brief getters
		 * @return vertex A
		 */
		Vec2D getB() { return b; }

		/**
		 * @brief getters
		 * @return vertex A
		 */
		Vec2D getC() { return c; }
	};
}


#endif /* TRIANGLE_H */
