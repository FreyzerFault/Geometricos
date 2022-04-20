#include "DrawAABB.h"

GEO::DrawAABB::DrawAABB (const AABB& aabb): Draw(), _aabb (aabb){
	
	_vertices = _aabb.getAABBVertices();
	
	for (int i = 0; i < 12 * 3; i++)
	{
		_normals.emplace_back(0,0,1);
		_indices.push_back(i);
	}

	buildVAO ();
}


void GEO::DrawAABB::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawAABB::drawIt (){
	
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::WIREFRAME );
	Scene::getInstance ()->addModel ( this );
	
//    for (int i=0; i<dsegment.size(); i++)
//        dsegment[i].drawIt();
	
}

