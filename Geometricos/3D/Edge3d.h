#pragma once

#include "Vec3D.h"

namespace GEO
{
	class Edge3D
	{
	protected:
		Vec3D _orig, _dest;

	protected:
		// t entre [0,1]
		virtual bool isTvalid(double t) const;
		
		// parametro t que coincide con el punto mas cercano de la recta a un punto
		virtual double getNearestT(const Vec3D& p) const;
		virtual Vec3D getNearestPoint(const Vec3D& p) const;

	public:
		Edge3D(const Vec3D& orig, const Vec3D& dest);
		
		Edge3D(const Edge3D& edge) = default;

		virtual ~Edge3D() = default;

		// Punto en la Parametrica por t
		virtual Vec3D getPoint(double t) const;
		
		double distance(const Vec3D& p) const;


		// Vector normal por un punto p
		virtual Vec3D normal(const Vec3D& p = Vec3D(0,0,0)) const;
		
		Vec3D getDest() const { return _dest; }
		Vec3D getOrig() const { return _orig; }

		// Devuelve un vector con las Coordenadas {ax, ay, az, bx, by, bz}
		std::vector<double> getVertices() const;
		
		Edge3D& operator=(const Edge3D& edge) = default;
		
		virtual void out();
	};

}

