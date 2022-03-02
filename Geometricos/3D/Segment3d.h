
/* 
 * File:   Segment3d.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:30
 */
#pragma once

#include "Edge3d.h"

namespace GEO
{
	/**
*	@brief This class represent a segment formed by two points.
*	@author Lidia Mª Ortega Alvarado.
*/
	class Segment3d : public Edge3d
	{
	protected:
		/**
		*	@brief Checks if the parametric value t is between 0 and 1 as a segment is not infinite.
		*/
		virtual bool isTvalid(double t) { return (t >= 0.0f && t <= 1.0f); }

	public:
		/**
		*	@brief Creates a segment with default point values.
		*/
		Segment3d() {};

		/**
		*	@brief Constructor.
		*/
		Segment3d(Vec3D& orig, Vec3D& dest);

		/**
		*	@brief Copy constructor.
		*/
		Segment3d(const Segment3d& segment);

		/**
		*	@brief Destructor.
		*/
		virtual ~Segment3d();

		/**
		*	@brief Assignment operator.
		*/
		virtual Segment3d& operator=(const Segment3d& segment);

		/**
		*	@brief Shows the segment data at the debug window.
		*/
		virtual void out();
	};

}

