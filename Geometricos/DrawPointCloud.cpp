
#include "DrawPointCloud.h"


GEO::DrawPointCloud::DrawPointCloud (PointCloud &t): dt (t), Draw(){
    
   //XXXXX

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

