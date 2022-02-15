#include "Vec2D.h"
#include "DrawLine.h"


GEO::DrawLine::DrawLine (Line &t): dt (t), Draw(){
	// Usando la Parametrica
	const Vec2D v(dt.getB() - dt.getA());
	Point inicio = dt.getPoint(-1000);
	Point fin = dt.getPoint(1000);

	_vertices.emplace_back(inicio.getX(), inicio.getY(), 0.0);
	_vertices.emplace_back(fin.getX(), fin.getY(), 0.0);
	
	
	_normals.emplace_back(0, 0, 1);
	_normals.emplace_back(0, 0, 1);
	

	_indices.push_back ( 0 );
	_indices.push_back ( 1 );

	buildVAO ();
}


void GEO::DrawLine::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawLine::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::LINE );
	Scene::getInstance ()->addModel ( this );
}


