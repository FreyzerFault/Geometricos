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
		Plane(const Vec3D& p, const Vec3D& u, const Vec3D& v, bool arePoints);

		// Plano definido por un punto y su normal
		Plane(const Vec3D& p, const Vec3D& normal);
		
		Plane(const Plane& plane) = default;
		
		virtual ~Plane() = default;

		// p esta en el Plano
		bool coplanar(const Vec3D& p) const;

		// Distancia al punto p
		double distance(const Vec3D& p) const;

		// AX + BY + CZ + D = 0.
		double getA() const;
		double getB() const;
		double getC() const;
		double getD() const;

		// Vectores cualquiera del Plano normalizados
		Vec3D getV() const { return (_b - _a).normalize(); }
		Vec3D getU() const { return (_c - _a).normalize(); }

		// Punto cualquiera del plano
		Vec3D getP() const { return _a; }

		// Vector Normal
		Vec3D getNormal() const;

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

