#pragma once
#include <vector>

#include "Vec3D.h"
#include "AABB.h"
#include "Draw.h"

namespace GEO
{
	enum class TypeVoxel
	{
		NP,
		white,	// Fuera edl Modelo
		grey,	// Intersecciona con el Modelo
		black	// Dentro del Modelo
	};

	class Voxel : public AABB
	{
		std::vector<Vec3D> points;
		TypeVoxel type = TypeVoxel::NP;

		std::vector<Triangle3D*> tris;

	public:
		Voxel() = default;
		Voxel(const Vec3D& min, const Vec3D& max)
			: AABB(min, max) {}

		void add(const Vec3D& p) { points.push_back(p); }
		
		bool contains(const Vec3D p) const;

		bool remove(const Vec3D& p);


		TypeColor getColor() const;
	};
}
