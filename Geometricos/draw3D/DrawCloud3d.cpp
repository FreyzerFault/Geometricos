#include "DrawCloud3D.h"


GEO::DrawCloud3D::DrawCloud3D (const PointCloud3D &t): Draw(), dt (t){

	//TODO
	

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

