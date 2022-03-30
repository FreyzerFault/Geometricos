#pragma once
#include <vector>
#include "Vec3D.h"
#include "AABB.h"

namespace GEO
{
	enum class TypeVoxel
	{
		NP,
		white,	// Fuera edl Modelo
		grey,	// Intersecciona con el Modelo
		black	// Dentro del Modelo
	};

	class Voxel : AABB
	{
		std::vector<Vec3D> points;
		TypeVoxel type = TypeVoxel::NP;

	public:
		Voxel() = default;

		void add(const Vec3D& p) { points.push_back(p); }
		
		bool contains(const Vec3D p) const;

		bool remove(const Vec3D& p);

	};
}
