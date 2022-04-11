#include "TriangleModel.h"
#include "VoxelModel.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <utility>

static const std::string objPath = "obj/";

GEO::TriangleModel::TriangleModel(const std::string& name) {
	try
	{
		loadFile (objPath + name + ".obj");
	}
	catch ( std::runtime_error& e )
	{
		const std::string mensaje = "Model -> ";
		throw std::runtime_error ( mensaje + e.what () );
	}
}


void GEO::TriangleModel::loadFile (const std::string& pathfile )
{
	//cleaning ();
	vv.clear();
	vi.clear();
	vn.clear();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile ( pathfile,
			  aiProcess_JoinIdenticalVertices
			| aiProcess_Triangulate
			| aiProcess_GenSmoothNormals);
	//		| aiProcess_GenNormals);

	// Carga to lo que haya en el archivo como un único modelo
	if ( !scene || !scene->mRootNode
	|| scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE )
	{
	  const std::string mensaje = "cargarArchivo: error cargando el archivo "
						+ pathfile + " -> " + importer.GetErrorString ();
	 throw std::runtime_error ( mensaje );
	}

	processNodeAssimp ( scene->mRootNode, scene );

	//buildVAO ();

	//return *this;
}


/**
 * Método para procesar de manera recursiva un nodo de la estructura creada por
 * Assimp al cargar un archivo
 * @param node Nodo de la estructura de Assimp a procesar
 * @param scene Escena de Assimp con to el contenido cargado del archivo
 * @note Al procesar el nodo de manera recursiva, no se garantiza que se llegue
 *       a un desbordamiento de pila
 */
void GEO::TriangleModel::processNodeAssimp (const aiNode* node, const aiScene* scene )
{
	for ( int i = 0; i < node->mNumMeshes; i++ )
	{
		//aiMesh* malla = scene->mMeshes[node->mMeshes[i]];
		// processMeshAssimp (malla, scene );
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		processMeshAssimp ( mesh, scene );
	}

	for ( int i = 0; i < node->mNumChildren; i++ )
	{
		processNodeAssimp ( node->mChildren[i], scene );
	}
}


/**
 * Carga en el modelo la geometría de una malla creada por Assimp al importar
 * un archivo
 * @param mesh Malla creada por Assimp
 * @param scene Escena de Assimp con to el contenido cargado del archivo
 * @post Carga vértices, normales, coordenadas de textura (si hubiera) e índices
 */
void GEO::TriangleModel::processMeshAssimp (const aiMesh* mesh, const aiScene* scene )
{
	Vec3D ve, no;
	//unsigned ind;

	std::cout << "mNumVertices" << mesh->mNumVertices << std::endl;
	for ( int i = 0; i < mesh->mNumVertices; i++ )
	{
		ve.setX(mesh->mVertices[i].x); 
		ve.setY(mesh->mVertices[i].y); 
		ve.setZ(mesh->mVertices[i].z); 
		vv.push_back(ve);
		
		no.setX(mesh->mNormals[i].x); 
		no.setY(mesh->mNormals[i].y); 
		no.setZ(mesh->mNormals[i].z); 
		vn.push_back(no);


//		if ( malla->mTextureCoords[0] )
//		{
//		   glm::vec2 ct;
//		   ct.x = malla->mTextureCoords[0][i].x;
//		   ct.y = malla->mTextureCoords[0][i].y;
//		   _cTextura.push_back ( ct );
//		}
	}

	std::cout <<"mNumFaces: " <<  mesh->mNumFaces << std::endl;
	for ( int i = 0; i < mesh->mNumFaces; i++ )
	{
		const aiFace cara = mesh->mFaces[i];
		for ( int j = 0; j < cara.mNumIndices; j++ )
		{
			vi.push_back(cara.mIndices[j]);
		}
	}

	//for(int i=0; i<vi.size(); i++){
	//	std::cout << i << "->" ;
	//	std::cout << vi[i*9]<< "/"   << vi[i*9+1]<< "/" <<  vi[i*9+1]<< " "; 
	//	std::cout << vi[i*9+3]<< "/" << vi[i*9+4]<< "/" <<  vi[i*9+5]<< " ";
	//	std::cout << vi[i*9+6]<< "/" << vi[i*9+7]<< "/" <<  vi[i*9+8]<< std::endl;

	//	//Triangle3D t (ve[]);
	//}

	std::cout <<"tamaño de ve: " <<  vv.size() << std::endl;
	std::cout <<"tamaño de vn: " <<  vn.size() << std::endl;
	std::cout <<"tamaño de vi: " <<  vi.size() << std::endl;
}


bool GEO::TriangleModel::pointIntoMesh(const Vec3D& point) const
{
	// 2 Random RAYs
	const Ray3D ray1(point, Vec3D(rand(), rand(), rand()));
	const Ray3D ray2(point, Vec3D(rand(), rand(), rand()));

	std::vector<Vec3D> points1;
	std::vector<Vec3D> points2;
	std::vector<Triangle3D> tris1;
	std::vector<Triangle3D> tris2;

	rayTraversalExh(ray1, points1, tris1);
	rayTraversalExh(ray2, points2, tris2);

	const bool par1 = points1.size() % 2 == 0;
	const bool par2 = points2.size() % 2 == 0;

	// Si es PAR esta FUERA
	if (par1 && par2)
		return false;

	// Si es IMPAR esta DENTRO
	if (!par1 && !par2)
		return true;

	// Si hay discrepancia lanzamos otro
	const Ray3D ray3(point, Vec3D(rand(), rand(), rand()));
	std::vector<Vec3D> points3;
	std::vector<Triangle3D> tris3;
	rayTraversalExh(ray3, points3, tris3);

	// Si se repite PAR es que esta FUERA
	if (points3.size() % 2 == 0)
		return false;

	// Esta DENTRO si es IMPAR
	return true;
}

std::vector<GEO::Vec3D> GEO::TriangleModel::pointCloudIntoMesh(const PointCloud3D& pc, bool useVoxel) const
{
	std::vector<Vec3D> pointsInside;

	for (const Vec3D& point : pc.getPoints())
	{
		if (useVoxel ? getVoxelModel()->pointIntoMesh(point) : pointIntoMesh(point))
			pointsInside.push_back(point);
	}
	
	return pointsInside;
}

bool GEO::TriangleModel::rayTraversalExh(const Ray3D& r, Vec3D& p, Triangle3D& t) const
{
	double minDistance = BasicGeom::INFINITO;

	for (const Triangle3D& tri : getFaces())
	{
		Vec3D point;
		if (tri.rayIntersection(r, point))
		{
			const double d = (point - r.getOrig()).module();
			if (d < minDistance)
			{
				minDistance = d;
				t = tri;
				p = point;
			}
		}
	}

	if (minDistance < BasicGeom::INFINITO)
		return true;

	return false;
}

bool GEO::TriangleModel::rayTraversalExh(const Ray3D& r, std::vector<Vec3D>& p, std::vector<Triangle3D>& t) const
{
	for (const Triangle3D& tri : getFaces())
	{
		Vec3D point;
		if (tri.rayIntersection(r, point))
		{
			p.push_back(point);
			t.push_back(tri);
		}
	}

	if (!p.empty())
		return true;

	return false;

}

GEO::Triangle3D GEO::TriangleModel:: getFace(int i) const
{

	if (i > numTriangulos()) return {};  
	
	const Vec3D a = vv[vi[i*3]];
	const Vec3D b = vv[vi[i*3+1]];
	const Vec3D c = vv[vi[i*3+2]];
	
	return{a, b, c};
}

std::vector<GEO::Triangle3D> GEO::TriangleModel::getFaces() const
{
	std::vector<Triangle3D> result;
	result.reserve(numTriangulos());

	for (int i = 0; i < numTriangulos(); i++)
	{
		result.emplace_back(vv[vi[i*3]], vv[vi[i*3+1]], vv[vi[i*3+2]]);
	}
	return result;
}

void GEO::TriangleModel::generateTris()
{
	if (tris.empty())
	{
		const auto faces = getFaces();
		tris.reserve(faces.size());
		for (const Triangle3D& face : faces)
		{
			// Se almacenan una copia
			tris.push_back(face);
		}
	}
}


unsigned GEO::TriangleModel::numTriangulos () const
{
	return (unsigned) vi.size()/3;
}


GEO::PointCloud3D GEO::TriangleModel::getCloud() const
{
	return {vv};
}

GEO::AABB GEO::TriangleModel::getAABB() const
{
	// Es lo mismo que la Caja Envolvente de la nube de puntos
	return getCloud().getAABB();
}

GEO::VoxelModel* GEO::TriangleModel::generateVoxelModel(double voxelSize)
{
	// Si ya se genero y con el mismo voxelSize, no lo generamos otra vez
	if (voxelModel != nullptr && voxelModel->getVoxelSize() == voxelSize )
		return voxelModel;

	voxelModel = new VoxelModel(*this, voxelSize);
	return voxelModel;
}
