/* 
 * File:   Plane.h
 * Author: lidia
 *
 * Created on 26 de enero de 2021, 17:56
 */
#pragma once

#include "Line3d.h"
#include "Segment3d.h"
#include "Vec3D.h"

/**
*	@brief This class a represents a 3D plane represented by three points.
*	@author Lidia Mª Ortega Alvarado.
*/
namespace GEO
{
	class Plane
	{
	public:
		enum IntersectionType
		{
			POINT, SEGMENT, COPLANAR
		};

	public:
		class IntersectionLine
		{
			Vec3D _point;
			IntersectionType _type;
		};

	protected:
		Vec3D _a, _b, _c;

	public:
		/**
		*
		*	@param p in pi = p + u * lambda + v * mu -> r from the points (R, S, T).
		*	@param u in pi = p + u * lambda + v * mu -> d from the points (R, S, T).
		*	@param v in pi = p + u * lambda + v * mu -> t from the points (R, S, T).
		*	@param If arePoints is false, then params are p + u * lambda + v * mu, otherwise are points (R, S, T).
		*/
		Plane(Vec3D& p, Vec3D& u, Vec3D& v, bool arePoints);

		/**
		*	@brief Copy constructor.
		*/
		Plane(const Plane& plane);

		/**
		*	@brief Destructor.
		*/
		virtual ~Plane();

		/**
		*	@brief Returns true if p is in the plane.
		*/
		bool coplanar(Vec3D& point);

		/**
		*	@brief Distance between the plane and the point.
		*/
		double distance(Vec3D& point);

		/**
		*	@brief Returns A in AX + BY + CZ + D = 0.
		*/
		double getA();

		/**
		*	@brief Returns B in AX + BY + CZ + D = 0.
		*/
		double getB();

		/**
		*	@brief Returns C in AX + BY + CZ + D = 0.
		*/
		double getC();

		/**
		*	@return D in AX + BY + CZ + D = 0.
		*/
		double getD() { return (-1.0) * (getA() * _a.getX() + getB() * _a.getY() + getC() * _a.getZ()); }

		/**
		*	@brief Returns the normal vector of (A, B, C) in Ax + By + Cz + D = 0.
		*/
		Vec3D getNormal();

		/**
	*	@brief Calculates the intersection point of a line and this plane, if exists.
	*/
		bool intersect(Line3d& line, Vec3D& point);

		/**
	*	@brief Calculates the intersection point of three planes.
	*/
		bool intersect(Plane& pa, Plane& pb, Vec3D& pinter);

		/**
		*	@brief Calculates the intersection line of a plane with this plane.
		*/
		bool intersect(Plane& plane, Line3d& line);


		/**
		*	@brief Assignment operator.
		*/
		virtual Plane& operator=(const Plane& plane);

		/**
		*	@brief Shows the plane values at the debug window.
		*/
		virtual void out();
	};
}

