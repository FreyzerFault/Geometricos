#include "DrawAABB.h"
#include "DrawSegment3D.h"

#define minX min.getX()
#define minY min.getY()
#define minZ min.getZ()
#define maxX max.getX()
#define maxY max.getY()
#define maxZ max.getZ()

GEO::DrawAABB::DrawAABB (const AABB& aabb): Draw(), _aabb (aabb){
	const Vec3D min = aabb._min;
	const Vec3D max = aabb._max;

	_vertices.emplace_back(minX, minY, minZ);
	_vertices.emplace_back(minX, minY, maxZ);
	_vertices.emplace_back(minX, maxY, maxZ);

	_vertices.emplace_back(minX, minY, minZ);
	_vertices.emplace_back(minX, maxY, maxZ);
	_vertices.emplace_back(minX, maxY, minZ);

	_vertices.emplace_back(minX, minY, maxZ);
	_vertices.emplace_back(maxX, minY, maxZ);
	_vertices.emplace_back(maxX, maxY, maxZ);

	_vertices.emplace_back(minX, minY, maxZ);
	_vertices.emplace_back(maxX, maxY, maxZ);
	_vertices.emplace_back(minX, maxY, maxZ);

	_vertices.emplace_back(maxX, minY, maxZ);
	_vertices.emplace_back(maxX, minY, minZ);
	_vertices.emplace_back(maxX, maxY, minZ);

	_vertices.emplace_back(maxX, minY, maxZ);
	_vertices.emplace_back(maxX, maxY, minZ);
	_vertices.emplace_back(maxX, maxY, maxZ);

	_vertices.emplace_back(maxX, minY, minZ);
	_vertices.emplace_back(minX, minY, minZ);
	_vertices.emplace_back(maxX, maxY, minZ);

	_vertices.emplace_back(minX, minY, minZ);
	_vertices.emplace_back(minX, maxY, minZ);
	_vertices.emplace_back(maxX, maxY, minZ);

	_vertices.emplace_back(maxX, minY, maxZ);
	_vertices.emplace_back(minX, minY, maxZ);
	_vertices.emplace_back(maxX, minY, minZ);

	_vertices.emplace_back(minX, minY, minZ);
	_vertices.emplace_back(maxX, minY, minZ);
	_vertices.emplace_back(minX, minY, maxZ);

	_vertices.emplace_back(minX, maxY, maxZ);
	_vertices.emplace_back(maxX, maxY, maxZ);
	_vertices.emplace_back(maxX, maxY, minZ);

	_vertices.emplace_back(minX, maxY, maxZ);
	_vertices.emplace_back(maxX, maxY, minZ);
	_vertices.emplace_back(minX, maxY, minZ);

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

