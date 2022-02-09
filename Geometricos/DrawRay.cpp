
#include "Point.h"
#include "DrawRay.h"



DrawRay::DrawRay (RayLine &t): dt (t), Draw(){
    
    
       //XXXXX
    

    buildVAO ();
    
}


void DrawRay::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawRay::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}

