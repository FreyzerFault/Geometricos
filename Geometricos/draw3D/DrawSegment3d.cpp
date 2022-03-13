#include "DrawSegment3d.h"

#include "Scene.h"


GEO::DrawSegment3d::DrawSegment3d (const Segment3D& segment): dt (segment), Draw(){
	
	const Vec3D inicio = segment.getOrig();
	const Vec3D fin = segment.getDest();

	_vertices.emplace_back(inicio.getX(), inicio.getY(), inicio.getZ());
	_vertices.emplace_back(fin.getX(), fin.getY(), fin.getZ());
	
	const Vec3D normal = segment.normal();

	_normals.emplace_back(normal.getX(), normal.getY(), normal.getZ());
	_normals.emplace_back(normal.getX(), normal.getY(), normal.getZ());
	

	_indices.push_back ( 0 );
	_indices.push_back ( 1 );
	

	buildVAO ();
}


void GEO::DrawSegment3d::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawSegment3d::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::LINE );
	Scene::getInstance ()->addModel ( this );
}

