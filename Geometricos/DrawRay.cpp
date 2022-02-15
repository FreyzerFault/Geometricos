
#include "Point.h"
#include "DrawRay.h"

#include "Vector.h"


GEO::DrawRay::DrawRay (RayLine &t): dt (t), Draw(){

	// Usando la Parametrica
	Point inicio = dt.getA();
	Point fin = dt.getPoint(1000);

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

