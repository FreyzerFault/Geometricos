#pragma once

#include "Edge3D.h"

namespace GEO
{
	class Ray3D : public Edge3D
	{
	protected:
		// t >= 0
		bool isTvalid(const double t) const override { return t >= 0; }

	public:
		Ray3D(const Vec3D& orig, const Vec3D& dest);
		
		Ray3D(const Ray3D& ray) = default;

		~Ray3D() override = default;
		
		Ray3D& operator=(const Ray3D& ray);

		void out() override;
	};
}

