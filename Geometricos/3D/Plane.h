#pragma once

#include "Line3D.h"
#include "Segment3d.h"
#include "Vec3D.h"

namespace GEO
{
	class Plane
	{
	public:
		enum IntersectionType
		{
			POINT, SEGMENT, COPLANAR
		};

		struct IntersectionLine
		{
			Vec3D _point;
			IntersectionType _type;
		};

	protected:
		Vec3D _a, _b, _c;

	public:
		/**
		*	@param p in pi = p + u * lambda + v * mu -> r from the points (R, S, T).
		*	@param u in pi = p + u * lambda + v * mu -> d from the points (R, S, T).
		*	@param v in pi = p + u * lambda + v * mu -> t from the points (R, S, T).
		*	@param arePoints
		*	@param If arePoints is false, then params are p + u * lambda + v * mu, otherwise are points (R, S, T).
		*/
		Plane(Vec3D& p, Vec3D& u, Vec3D& v, bool arePoints);
		
		Plane(const Plane& plane) = default;
		
		virtual ~Plane() = default;

		// p esta en el Plano
		bool coplanar(Vec3D& p);

		// Distancia al punto p
		double distance(Vec3D& p);

		// AX + BY + CZ + D = 0.
		double getA() const;
		double getB() const;
		double getC() const;
		double getD() const;

		// Vector Normal
		Vec3D getNormal();

		// Punto de Interseccion de la linea con el Plano
		bool intersect(Line3D& line, Vec3D& point);

		// Punto de Interseccion entre 3 Planos
		bool intersect(Plane& pa, Plane& pb, Vec3D& pinter);

		// Linea de Interseccion entre 2 Planos
		bool intersect(Plane& plane, Line3D& line);

		Plane& operator=(const Plane& plane);
		
		virtual void out();
	};
}

