#include "TriangleModel.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <utility>


GEO::TriangleModel::TriangleModel(const std::string& pathFile) {
	try
	{
		loadFile (pathFile);
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
//void TriangleModel::processMeshAssimp (  aiMesh* mesh, const aiScene* scene )
void GEO::TriangleModel::processMeshAssimp (const aiMesh* mesh, const aiScene* scene )
{
	Vec3D ve, no;
	//unsigned ind;

	std::cout << "mNumVertices" << mesh->mNumVertices << std::endl;
	for ( int i = 0; i < mesh->mNumVertices; i++ )
	{
//		glm::vec3 v;
//		v.x = mesh->mVertices[i].x;
//		v.y = mesh->mVertices[i].y;
//		v.z = mesh->mVertices[i].z;
//		_vertices.push_back ( v );

		ve.setX(mesh->mVertices[i].x); 
		ve.setY(mesh->mVertices[i].y); 
		ve.setZ(mesh->mVertices[i].z); 
		vv.push_back(ve);

//		glm::vec3 n;
//		n.x = mesh->mNormals[i].x;
//		n.y = mesh->mNormals[i].y;
//		n.z = mesh->mNormals[i].z;
//		_normals.push_back ( n );
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
			//_indices.push_back ( cara.mIndices[j] );
			//ind = cara.mIndices[j];
			vi.push_back(cara.mIndices[j]);
		}
	}
   
	// for(int i=0; i<vi.size(); i++){
	//     std::cout << i << "->" ; 
	//     std::cout << vi[i*9]<< "/"   << vi[i*9+1]<< "/" <<  vi[i*9+1]<< " "; 
	//     std::cout << vi[i*9+3]<< "/" << vi[i*9+4]<< "/" <<  vi[i*9+5]<< " ";
	//     std::cout << vi[i*9+6]<< "/" << vi[i*9+7]<< "/" <<  vi[i*9+8]<< std::endl;
	//     
	//     Triangle3D t (ve[])
	// }   

	std::cout <<"tamaño de ve: " <<  vv.size() << std::endl;
	std::cout <<"tamaño de vn: " <<  vn.size() << std::endl;
	std::cout <<"tamaño de vi: " <<  vi.size() << std::endl;
}



GEO::Triangle3D GEO::TriangleModel:: getFace(int i) const
{

	if (i > numTriangulos()) return {};  
	
	const Vec3D a = vv[vi[i*3]];
	const Vec3D b = vv[vi[i*3+1]];
	const Vec3D c = vv[vi[i*3+2]];
	
	return{a, b, c};
}

std::vector<GEO::Triangle3D> GEO::TriangleModel::getFaces () const
{
	
	std::vector<Triangle3D> result;
	
	for (int i=0; i< numTriangulos(); i++){
		Vec3D a = vv[vi[i*3]];
		Vec3D b = vv[vi[i*3+1]];
		Vec3D c = vv[vi[i*3+2]];
		
		Triangle3D tri (a,b,c);
		result.push_back(tri);
	}
	return result;
}


unsigned GEO::TriangleModel:: numTriangulos () const
{
	
	return (unsigned) vi.size()/3;
	
	//std::cout << (unsigned) vi.size()/3 << std::endl;
	//std::cout << "vn " << vn.size() << std::endl;
	//std::cout << "vv " << vv.size() << std::endl;
	//
	//return vi.size();
	
}


GEO::PointCloud3D GEO::TriangleModel:: getCloud () const
{
	PointCloud3D pc (vv);
	return pc;
}
