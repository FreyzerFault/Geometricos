
#include "DrawPointCloud.h"


DrawPointCloud::DrawPointCloud (PointCloud &t): dt (t), Draw(){
    
   //XXXXX

    buildVAO ();
    
}


void DrawPointCloud::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawPointCloud::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}

