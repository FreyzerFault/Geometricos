
/* 
 * File:   Edge3d.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:55
 */
#pragma once

#include "Vec3D.h"

namespace GEO
{
	/**
*	@brief Represents any line of the geometry module.
*
*/
	class Edge3d
	{
	protected:
		Vec3D _orig, _dest;

	protected:
		/**
		*	@brief Checks if the parametric t values is valid for our subclass.
		*/
		virtual bool isTvalid(double t) = 0;

	public:
		/**
		*	@brief Default constructor.
		*/
		Edge3d();

		/**
		*	@brief Constructor.
		*/
		Edge3d(Vec3D& orig, Vec3D& dest);

		/**
		*	@brief Copy constructor.
		*/
		Edge3d(const Edge3d& edge);

		/**
		*	@brief Destructor.
		*/
		virtual ~Edge3d();

		/**
		*	@brief Returns the destination point.
		*/
		Vec3D getDestination();

		/**
		*	@brief Returns the initial point.
		*/
		Vec3D getOrigin();

		/**
		*	@brief Returns a point given the parametric value. It may be wrong if the t value is not valid for the specific subclass.
		*/
		virtual Vec3D getPoint(double t);

		/**
		*	@brief Returns a vector with all the coordinate values of the segment (origin and dest).
		*/
		std::vector<double> getVertices();

		/**
		*	@brief Assignment operator.
		*/
		virtual Edge3d& operator=(const Edge3d& edge);

		/**
		*	@brief Shows the values of the edge at the debug window.
		*/
		virtual void out();
	};

}

