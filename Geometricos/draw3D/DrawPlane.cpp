
/* 
 * File:   DrawPlane.cpp
 * Author: lidia
 * 
 * Created on 28 de enero de 2021, 17:11
 */


#include "DrawPlane.h"


GEO::DrawPlane::DrawPlane (Plane &t): dt (t), Draw(){
    
    
    //XXXX


     buildVAO ();
    
}


void GEO::DrawPlane::drawIt (GEO::TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawPlane::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(GEO::TypeDraw::POLYGON );
    GEO::Scene::getInstance ()->addModel ( this );
    
}

