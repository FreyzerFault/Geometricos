
/* 
 * File:   Ray3d.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:22
 */
#pragma once

#include "Edge3d.h"

namespace GEO
{
	/**
*	@brief This class represents a ray that goes from an origin to the infinite.
*	@author Lidia Mª Ortega Alvarado.
*/
	class Ray3d : public Edge3d
	{
	protected:
		/**
		*	@brief Checks if the parametric value t is valid. It is only invalid if t is smaller than 0.
		*/
		virtual bool isTvalid(double t) { return (t >= 0); }

	public:
		/**
		*	@brief Constructor.
		*/
		Ray3d(Vec3D& orig, Vec3D& dest);

		/**
		*	@brief Copy constructor.
		*/
		Ray3d(const Ray3d& ray);

		/**
		*	@brief Destructor.
		*/
		virtual ~Ray3d();

		/**
		*	@brief Assignment operator.
		*/
		virtual Ray3d& operator=(const Ray3d& ray);

		/**
		*	@brief Shows some information about the ray at the debug window.
		*/
		virtual void out();
	};
}

