#pragma once

#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <string>
#include <vector>
#include "Triangle3D.h"
#include "PointCloud3D.h"
#include "Vec3D.h"
#include "VoxelModel.h"

namespace GEO
{
	class VoxelModel;

	class TriangleModel {

		friend class DrawTriangleModel;

	private:
		//aiMesh* vmesh;
		std::vector<Vec3D> vv;  // vector de vértices
		std::vector<Vec3D> vn;  // vector de normales
		std::vector<unsigned> vi; //vector de índices

		VoxelModel* voxelModel;

		void loadFile(const std::string& pathfile);
		void processMeshAssimp(const aiMesh* mesh, const aiScene* scene);
		void processNodeAssimp(const aiNode* node, const aiScene* scene);

	public:
		TriangleModel(const std::string& pathfile);

		TriangleModel(const TriangleModel& orig) = default;
		virtual ~TriangleModel() = default;

		// Detecta si el punto esta dentro de la Malla
		bool pointIntoMesh(const Vec3D& point) const;

		// Interseccion de un RAYO con el modelo
		// t es el Triangulo Intersectado mas cercano, p el punto de interseccion
		bool rayTraversalExh(const Ray3D& r, Vec3D& p, Triangle3D& t) const;


		// Todas las Intersecciones de un RAYO con el modelo
		// t es la lista de Triangulos con los que Intersecta, y p los puntos
		bool rayTraversalExh(const Ray3D& r, std::vector<Vec3D>& p, std::vector<Triangle3D>& t) const;

		Triangle3D getFace(int i) const;
		std::vector<Triangle3D> getFaces() const;

		unsigned numTriangulos() const;

		PointCloud3D getCloud() const;

		AABB getAABB() const;

		VoxelModel* generateVoxelModel(double voxelSize = defaultVoxelSize);

		VoxelModel* getVoxelModel() const { return voxelModel; }
	};
}

