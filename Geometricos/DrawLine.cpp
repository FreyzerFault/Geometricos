#include "Point.h"
#include "DrawLine.h"
#include "Line.h"


GEO::DrawLine::DrawLine (Line &t): dt (t), Draw(){
    
 //XXXX
    

    buildVAO ();
    
}


void GEO::DrawLine::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawLine::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}


