#include "DrawCloud3D.h"

#include "DrawVec3D.h"


GEO::DrawCloud3D::DrawCloud3D (const PointCloud3D& pointCloud): Draw(), pc (pointCloud){
	if (pointCloud.getPCLPoints().empty())
	{
		for (int i = 0; i < pointCloud.getPoints().size(); ++i)
		{
			const Vec3D& point = pointCloud.getPoint(i);
			_vertices.emplace_back(point.getX(), point.getY(), point.getZ());
			_normals.emplace_back(0, 0, 1);
			_indices.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < pointCloud.getPCLPoints().size(); ++i)
		{
			const pcl::PointXYZRGB& point = pointCloud.getPCLPoint(i);
			_vertices.emplace_back(point.x, point.y, point.z);
			_normals.emplace_back(0, 0, 1);
			_indices.push_back(i);
		}
	}
	
	buildVAO ();
	
}



void GEO::DrawCloud3D::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawCloud3D::drawIt (){
	if (pc.getPCLPoints().empty())
	{
		setShaderProgram ( "algeom" );
		setDrawMode(TypeDraw::POINT );
		Scene::getInstance ()->addModel ( this );
	}
	else
	{
		// Creamos un DrawPoint por cada punto para aplicarle el color
		for (const pcl::PointXYZRGB& point : pc.getPCLPoints())
		{
			Vec3D v3D(point.x, point.y, point.z);
			drawPoints.emplace_back(v3D);

			const TypeColor color(point.r, point.g, point.b);
			drawPoints.back().drawIt(color);
		}
	}
}

