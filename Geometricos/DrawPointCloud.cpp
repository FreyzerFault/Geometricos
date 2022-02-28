
#include "DrawPointCloud.h"


GEO::DrawPointCloud::DrawPointCloud (const PointCloud &t): Draw(), dt (t){
	const auto& points = dt.getPoints();
	for (int i = 0; i < points.size(); ++i)
	{
		_vertices.emplace_back(points[i].getX(), points[i].getY(), 0.0);
		_normals.emplace_back(0, 0, 1);
		_indices.push_back(i);
	}

	buildVAO ();
}


void GEO::DrawPointCloud::drawIt (TypeColor c){
	setColorActivo (c);
	drawIt();
}


void GEO::DrawPointCloud::drawIt (){
	setShaderProgram ( "algeom" );
	setDrawMode(TypeDraw::POINT );
	Scene::getInstance ()->addModel ( this );
	
}

