
/* 
 * File:   Line3d.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:55
 */
#pragma once

#include "Edge3d.h"
#include "Line3d.h"

namespace GEO
{

	class Line3d : public Edge3d
	{
	public:
		enum classifyLines { NON_INTERSECT, PARALLEL, INTERSECT, THESAME };

	protected:
		/**
		*	@brief Checks if the parametric value t is valid. Any value is valid for a line.
		*/
		virtual bool isTvalid(double t) { return true; }

	public:
		/**
		*	@brief Default constructor.
		*/
		Line3d();

		/**
		*	@brief Constructor.
		*/
		Line3d(Vec3D& orig, Vec3D& dest);

		/**
		*	@brief Copy constructor.
		*/
		Line3d(const Line3d& line);

		/**
		*	@brief Destructor.
		*/
		virtual ~Line3d();

		/**
		*	@brief Distance between two lines.
		*/
		double distance(Line3d& line);


		/**
		*    @brief Distance between point p and this.
		*/
		double distance(Vec3D& p);

		/**
		*	@brief Returns the normal to this line that passes through p.
		*/
		Line3d normalLine(Vec3D& p);

		/**
		*	@brief Assignment operator.
		*/
		virtual Line3d& operator=(const Line3d& line);

		/**
		*	@brief Shows line data at the debug window.
		*/
		virtual void out();


	};
}

