#include "Vec2D.h"
#include "DrawLine.h"
#include "Scene.h"


GEO::DrawLine::DrawLine (const Line &line): Draw(), _line (&line){
	// Usando la Parametrica
	const Vec2D v(_line->getB() - _line->getA());
	const Point inicio = _line->getPoint(-1000);
	const Point fin = _line->getPoint(1000);

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


