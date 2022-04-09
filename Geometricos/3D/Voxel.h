#pragma once
#include <vector>

#include "Vec3D.h"
#include "AABB.h"
#include "Draw.h"

namespace GEO
{
	class TriangleModel;

	enum class TypeVoxel
	{
		NP,
		out,	// Fuera edl Modelo
		intersect,	// Intersecciona con el Modelo
		in,	// Dentro del Modelo
	};

	class Voxel : public AABB
	{
		std::vector<Vec3D> points;
		TypeVoxel type = TypeVoxel::NP;

		std::vector<const Triangle3D*> tris;

	public:
		Voxel() = default;
		Voxel(const Vec3D& min, const Vec3D& max)
			: AABB(min, max) {}

		void add(const Vec3D& p) { points.push_back(p); }
		
		bool contains(const Vec3D p) const;

		bool remove(const Vec3D& p);

		std::vector<const Triangle3D*>& getTris() { return tris; }

		void checkTris(const TriangleModel& triModel);

		TypeVoxel getType() const { return type; }
		TypeColor getColor() const;
	};
}
