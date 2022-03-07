
#include "Point.h"
#include "DrawRay.h"
#include "Scene.h"


GEO::DrawRay::DrawRay (const RayLine &t): Draw(), ray (&t){

	// Usando la Parametrica
	const Point inicio = ray->getA();
	const Point fin = ray->getPoint(1000);

	_vertices.emplace_back(inicio.getX(), inicio.getY(), 0.0);
	_vertices.emplace_back(fin.getX(), fin.getY(), 0.0);
	
	_normals.emplace_back(0, 0, 1);
	_normals.emplace_back(0, 0, 1);

	_indices.push_back ( 0 );
	_indices.push_back ( 1 );

	buildVAO ();
	
}


void GEO::DrawRay::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawRay::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::LINE );
	Scene::getInstance ()->addModel ( this );
}

