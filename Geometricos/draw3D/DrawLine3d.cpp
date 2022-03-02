#include "Point.h"
#include "DrawLine3d.h"
#include "Line3d.h"


GEO::DrawLine3d::DrawLine3d (Line3d &t): dt (t), Draw(){
    
    //XXX
    

    buildVAO ();
    
}


void GEO::DrawLine3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawLine3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}



