#include "DrawVec3D.h"


GEO::DrawVec3D::DrawVec3D (const Vec3D &p): Draw(), dp (p){

	_vertices.emplace_back(p.getX(), p.getY(), p.getZ());
	_normals.emplace_back(0, 0, 1);
	_indices.push_back(0);
	
	buildVAO ();
}

void GEO::DrawVec3D::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}



void GEO::DrawVec3D::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::POINT );
	Scene::getInstance ()->addModel ( this );
	
}
