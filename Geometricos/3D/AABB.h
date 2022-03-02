
/* 
 * File:   AABB.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:10
 */
#pragma once

#include "Vec3D.h"

namespace GEO
{
	class Triangle3D;

	class AABB
	{

		friend class DrawAABB;
	protected:
		Vec3D _min, _max;								// Edge points of the cube.

	public:
		/**
		*	@brief Default constructor.
		*/
		AABB();

		/**
		*	@brief Constructor.
		*/
		AABB(Vec3D& min, Vec3D& max);

		/**
		*	@brief Copy constructor,
		*/
		AABB(const AABB& aabb);

		/**
		*	@brief Destructor.
		*/
		virtual ~AABB();




		/**
		*	@brief Returns the central point of the cube.
		*/
		Vec3D getCenter();

		/**
		*	@brief Returns the vector that goes from the center to the maximum point.
		*/
		Vec3D getExtent();

		/**
		*	@brief Returns the lowest corner of the cube.
		*/
		Vec3D getMin() { return _min; }

		/**
		*	@brief Returns the maximum points of the cube.
		*/
		Vec3D getMax() { return _max; }

		/**
		*	@brief Assignment operator.
		*/
		AABB& operator=(const AABB& orig);

		/**
		*	@brief Modifies the minimum point.
		*/
		void setMin(Vec3D& min) { min = min; }

		/**
		*	@brief Modifies the maximum point.
		*/
		void setMax(Vec3D& max) { max = max; }
	};
}

