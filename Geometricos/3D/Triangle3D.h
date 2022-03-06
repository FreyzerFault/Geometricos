/* 
 * File:   Triangle3D.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:14
 */
#pragma once



#include "AABB.h"
#include "Plane.h"
#include "Ray3D.h"
#include "Segment3d.h"
#include "Vec3D.h"

namespace GEO
{
	/**
*	@brief This class represents a triangle defined by 3 points.
*	@author Lidia Mª Ortega Alvarado.
*/
	class Triangle3D
	{
	public:

		friend class DrawTriangle3d;

		enum PointPosition
		{
			POSITIVE, NEGATIVE, COPLANAR
		};

		enum PointTrianglePosition
		{
			PARALELL, COLLINEAR, INTERSECTS, NO_INTERSECTS
		};

		// Contains all those attributes necessary for resolving the intersection between a triangle and an AABB.
		struct TriangleAABBIntersData
		{
			Vec3D _v0, _v1, _v2;
			float _min, _max, _rad;
			Vec3D _normal, _edge0, _edge1, _edge2, _p, _fedge;
			Vec3D _boxCenter;
			Vec3D _boxRadius;
		};

	protected:
		Vec3D _a, _b, _c;


	public:
		/**
		*	@brief Default constructor.
		*/
		Triangle3D();

		/**
		*	@brief Constructor.
		*/
		Triangle3D(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz);

		/**
		*	@brief Copy constructor.
		*/
		Triangle3D(const Triangle3D& triangle);

		/**
		*	@brief Constructor.
		*/
		Triangle3D(const Vec3D& va, const Vec3D& vb, const Vec3D& vc);

		/**
		*	@brief Destructor.
		*/
		virtual ~Triangle3D();

		/**
		*	@brief Returns the are of the triangle.
		*/
		double area() const;

		/**
		*	@brief Returns the position of the point respect to the triangle plane.
		*/
		PointPosition classify(Vec3D& point);

		/**
		*	@brief Returns a new triangle with the same values than this one.
		*/
		Triangle3D copy() { return Triangle3D(_a, _b, _c); }



		/**
		*	@brief Returns the first point.
		*/
		Vec3D getA() { return _a; }

		/**
		*	@brief Returns the second point.
		*/
		Vec3D getB() { return _b; }

		/**
		*	@brief Returns the third point.
		*/
		Vec3D getC() { return _c; }


		/**
		*	@brief Returns the normal of the triangle.
		*/
		Vec3D normal();

		/**
		*	@brief Assignment operator.
		*/
		virtual Triangle3D& operator=(const Triangle3D& triangle);

		/**
		*	@brief Shows some information about the triangle at the debug window.
		*/
		virtual void out();


		/**
		*	@brief Modifies the first point.
		*/
		void setA(Vec3D& pa) { _a = pa; }

		/**
		*	@brief Modifies the second point.
		*/
		void setB(Vec3D& pb) { _b = pb; }

		/**
		*	@brief Modifies the third point.
		*/
		void setC(Vec3D& pc) { _c = pc; }

		/**
		*	@brief Modifies all the points.
		*/
		void set(Vec3D& va, Vec3D& vb, Vec3D& vc);


	};
}

