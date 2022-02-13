
#include "Point.h"
#include "DrawRay.h"


GEO::DrawRay::DrawRay (RayLine &t): dt (t), Draw(){
    
    
       //XXXXX
    

    buildVAO ();
    
}


void GEO::DrawRay::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawRay::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}

