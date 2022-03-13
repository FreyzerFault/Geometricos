#include "DrawAABB.h"
#include "DrawSegment3D.h"


GEO::DrawAABB::DrawAABB (const AABB& aabb): Draw(), _aabb (aabb){
	const Vec3D min = aabb._min;
	const Vec3D max = aabb._max;

	_vertices.emplace_back(min.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(min.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(min.getX(), max.getY(), max.getZ());

	_vertices.emplace_back(min.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(min.getX(), max.getY(), max.getZ());
	_vertices.emplace_back(min.getX(), max.getY(), min.getZ());

	_vertices.emplace_back(min.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), max.getZ());

	_vertices.emplace_back(min.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(min.getX(), max.getY(), max.getZ());

	_vertices.emplace_back(max.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), min.getZ());

	_vertices.emplace_back(max.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), min.getZ());
	_vertices.emplace_back(max.getX(), min.getY(), max.getZ());

	_vertices.emplace_back(max.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(min.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), min.getZ());

	_vertices.emplace_back(min.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(min.getX(), max.getY(), min.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), min.getZ());

	_vertices.emplace_back(max.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(min.getX(), min.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), min.getY(), min.getZ());

	_vertices.emplace_back(min.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(max.getX(), min.getY(), min.getZ());
	_vertices.emplace_back(min.getX(), min.getY(), max.getZ());

	_vertices.emplace_back(min.getX(), max.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), min.getZ());

	_vertices.emplace_back(min.getX(), max.getY(), max.getZ());
	_vertices.emplace_back(max.getX(), max.getY(), min.getZ());
	_vertices.emplace_back(min.getX(), max.getY(), min.getZ());

	for (int i = 0; i < 12; i++)
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

