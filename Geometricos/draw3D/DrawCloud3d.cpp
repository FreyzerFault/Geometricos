#include "DrawCloud3D.h"

#include "DrawVec3D.h"


GEO::DrawCloud3D::DrawCloud3D (const PointCloud3D& pointCloud): Draw(), pc (pointCloud){
	if (pointCloud.getPCLPoints().empty())
	{
		for (int i = 0; i < pointCloud.getPointsSize(); ++i)
		{
			const Vec3D& point = pointCloud.getPoint(i);
			_vertices.emplace_back(point.getX(), point.getY(), point.getZ());
			_normals.emplace_back(0, 0, 1);
			_indices.push_back(i);
		}
	}
	else
	{
		for (pcl::PointXYZ& point : pointCloud.getPCLPoints())
		{
			_vertices.emplace_back(point.x, point.y, point.z);
		}

		addDefaultNormals(pointCloud.getPCLPointsSize());
		addSequencialIndices(pointCloud.getPCLPointsSize());
	}
	
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

