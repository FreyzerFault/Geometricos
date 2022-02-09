#include "Point.h"
#include "DrawLine.h"
#include "Line.h"



DrawLine::DrawLine (Line &t): dt (t), Draw(){
    
 //XXXX
    

    buildVAO ();
    
}


void DrawLine::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawLine::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}


