#include "DrawCloud3D.h"

#include "DrawVec3D.h"


GEO::DrawCloud3D::DrawCloud3D (const PointCloud3D& pointCloud): Draw(), pc (pointCloud){

	for (int i = 0; i < pointCloud.getPointsSize(); ++i)
	{
		const Vec3D& point = pointCloud.getPoint(i);
		_vertices.emplace_back(point.getX(), point.getY(), point.getZ());
	}

	addDefaultNormals(pointCloud.getPointsSize());
	addSequencialIndices(pointCloud.getPointsSize());
	
	buildVAO ();
	
}



void GEO::DrawCloud3D::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawCloud3D::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::POINT );
	Scene::getInstance ()->addModel ( this );
}

