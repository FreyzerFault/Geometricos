#pragma once
#include <vector>

#include "Vec3D.h"
#include "AABB.h"
#include "Draw.h"
#include "VoxelGrid.h"

namespace GEO
{
	class VoxelGrid;
	class VoxelModel;
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

		VoxelGrid* voxelGrid;
		Vec3D gridCoord;

		// Triangulos con los que intersecta
		std::vector<const Triangle3D*> tris;

	public:
		Voxel() = default;
		Voxel(const Vec3D& min, const Vec3D& max, VoxelGrid* voxelGrid = nullptr);

		// Metodos propios de una Casilla de una Malla Regular
		void add(const Vec3D& p) { points.push_back(p); }
		bool contains(const Vec3D& p) const;
		bool remove(const Vec3D& p);

		// Lista de triangulos del modelo con los que intersecta
		std::vector<const Triangle3D*>& getTris() { return tris; }

		// Busca los triangulos con los que intersecta en el modelo y almacena sus indices
		void checkTris(const TriangleModel& triModel);

		// Numero de puntos dentro del voxel
		int poblacion() const { return points.size(); }
		int poblacionCercana() const; // Todos los vecinos + self

		// Tipo de voxel: in / out / intersect
		TypeVoxel getType() const { return type; }

		// Color asociado al tipo del voxel
		TypeColor getColor() const;
	};
}
