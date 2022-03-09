#include "Point.h"
#include "DrawLine3D.h"
#include "Line3D.h"
#include "Scene.h"


GEO::DrawLine3D::DrawLine3D (const Line3D& line): Draw(), dt (line){
	const Vec3D inicio = line.getPoint(-BasicGeom::BIGNUM);
	const Vec3D fin = line.getPoint(BasicGeom::BIGNUM);

	_vertices.emplace_back(inicio.getX(), inicio.getY(), inicio.getZ());
	_vertices.emplace_back(fin.getX(), fin.getY(), fin.getZ());

	const Vec3D normal = line.normal();

	_normals.emplace_back(normal.getX(), normal.getY(), normal.getZ());
	_normals.emplace_back(normal.getX(), normal.getY(), normal.getZ());
	

	_indices.push_back ( 0 );
	_indices.push_back ( 1 );

	buildVAO ();
}


void GEO::DrawLine3D::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawLine3D::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::LINE );
	Scene::getInstance ()->addModel ( this );
}



