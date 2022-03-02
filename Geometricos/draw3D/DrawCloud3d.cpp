
/* 
 * File:   DrawCloud3d.cpp
 * Author: lidia
 * 
 * Created on 28 de enero de 2021, 12:27
 */

#include "DrawCloud3d.h"


GEO::DrawCloud3d::DrawCloud3d (PointCloud3d &t): dt (t), Draw(){
    
    //XXXX
    

    buildVAO ();
    
}



void GEO::DrawCloud3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawCloud3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}

