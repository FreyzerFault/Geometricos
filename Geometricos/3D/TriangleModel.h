#pragma once

#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <string>
#include <vector>
#include "Triangle3D.h"
#include "PointCloud3D.h"
#include "Vec3D.h"

namespace GEO
{
	class TriangleModel {

		friend class DrawTriangleModel;

	private:
		//aiMesh* vmesh;
		std::vector<Vec3D> vv;  // vector de vértices
		std::vector<Vec3D> vn;  // vector de normales
		std::vector<unsigned> vi; //vector de índices

		void loadFile(const std::string& pathfile);
		void processMeshAssimp(const aiMesh* mesh, const aiScene* scene);
		void processNodeAssimp(const aiNode* node, const aiScene* scene);

	public:
		TriangleModel(const std::string& pathfile);

		TriangleModel(const TriangleModel& orig) = default;
		virtual ~TriangleModel() = default;

		Triangle3D getFace(int i) const;
		std::vector<Triangle3D> getFaces() const;

		unsigned numTriangulos() const;

		PointCloud3D getCloud() const;
	};
}

