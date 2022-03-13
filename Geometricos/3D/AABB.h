#pragma once

#include "Vec3D.h"

namespace GEO
{
	class Triangle3D;

	class AABB
	{

		friend class DrawAABB;
	protected:
		Vec3D _min, _max;								// Edge points of the cube.

	public:

		AABB();
		
		AABB(const Vec3D& min, const Vec3D& max);
		
		AABB(const AABB& aabb) = default;
		
		virtual ~AABB() = default;


		// Punto central
		Vec3D getCenter() const;

		// Vector [Centro -> Max Point]
		Vec3D getExtent() const;

		Vec3D getMin() const { return _min; }
		Vec3D getMax() const { return _max; }

		void setMin(const Vec3D& min) { _min = min; }
		void setMax(const Vec3D& max) { _max = max; }


		AABB& operator=(const AABB& orig) = default;
	};
}

