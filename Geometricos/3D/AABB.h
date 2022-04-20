#pragma once

#include <glm/vec3.hpp>

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

		AABB() = default;
		
		AABB(const Vec3D& min, const Vec3D& max)
		: _min(min), _max(max) {}
		
		AABB(const AABB& aabb) = default;
		
		virtual ~AABB() = default;

		// Interseccion AABB-Tri
		bool AABBtri(const Triangle3D& tri) const;

		// Punto contenido en el AABB
		bool pointInAABB(const Vec3D& point) const;

		// Punto central
		Vec3D getCenter() const;

		// Vector [Centro -> Max Point]
		Vec3D getExtent() const;

		Vec3D getMin() const { return _min; }
		Vec3D getMax() const { return _max; }

		void setMin(const Vec3D& min) { _min = min; }
		void setMax(const Vec3D& max) { _max = max; }


		AABB& operator=(const AABB& orig) = default;

		std::vector<glm::vec3> getAABBVertices() const;
	};
}

