
/* 
 * File:   TriangleModel.h
 * Author: lidia
 *
 * Created on 20 de febrero de 2021, 10:41
 */
#pragma once

#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <string>
#include <vector>
#include "Triangle3D.h"
#include "PointCloud3d.h"
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

        void loadFile(std::string pathfile);
        void processMeshAssimp(aiMesh* mesh, const aiScene* scene);
        void processNodeAssimp(aiNode* node, const aiScene* scene);

    public:
        TriangleModel(std::string pathfile);
        TriangleModel(const TriangleModel& orig);
        virtual ~TriangleModel();
        Triangle3D getFace(int i);
        unsigned numTriangulos();
        std::vector<Triangle3D> getFaces();
        PointCloud3d getCloud();

    };
}

