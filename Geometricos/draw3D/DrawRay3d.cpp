#include "Vec3D.h"
#include "DrawRay3d.h"

#include "BasicGeom.h"
#include "Scene.h"


GEO::DrawRay3d::DrawRay3d (const Ray3D &ray): Draw(), dt (ray){
	
	const Vec3D inicio = ray.getOrig();
	const Vec3D fin = ray.getPoint(BasicGeom::INFINITO);

	_vertices.emplace_back(inicio.getX(), inicio.getY(), inicio.getZ());
	_vertices.emplace_back(fin.getX(), fin.getY(), fin.getZ());
	
	const Vec3D normal = ray.normal();

	_normals.emplace_back(normal.getX(), normal.getY(), normal.getZ());
	_normals.emplace_back(normal.getX(), normal.getY(), normal.getZ());
	

	_indices.push_back ( 0 );
	_indices.push_back ( 1 );

	buildVAO ();
	
}


void GEO::DrawRay3d::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawRay3d::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::LINE );
	Scene::getInstance ()->addModel ( this );
}


