#pragma once

#include "AABB.h"
#include "Plane.h"
#include "Ray3D.h"
#include "Segment3d.h"
#include "Vec3D.h"

namespace GEO
{
	class Triangle3D
	{
	public:

		friend class DrawTriangle3D;

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
		Triangle3D() = default;
		
		Triangle3D(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz);

		Triangle3D(const Vec3D& va, const Vec3D& vb, const Vec3D& vc);

		Triangle3D(const Triangle3D& triangle) = default;

		virtual ~Triangle3D() = default;
		
		double area() const;

		// Posicion relativa de un punto respecto al triangulo
		PointPosition classify(const Vec3D& point) const;

		Vec3D normal() const;

		Vec3D getA() { return _a; }
		Vec3D getB() { return _b; }
		Vec3D getC() { return _c; }

		void setA(const Vec3D& pa) { _a = pa; }
		void setB(const Vec3D& pb) { _b = pb; }
		void setC(const Vec3D& pc) { _c = pc; }

		void set(const Vec3D& va, const Vec3D& vb, const Vec3D& vc);


		Triangle3D& operator=(const Triangle3D& triangle) = default;
		
		virtual void out();

		


	};
}

