
/* 
 * File:   DrawPoint.cpp
 * Author: lidia
 * 
 * Created on 14 de enero de 2021, 15:02
 */

#include "DrawPoint.h"



DrawPoint::DrawPoint (Point &p): dp (p), Draw(){
    

    _vertices.push_back (glm::vec3(p.getX(), p.getY(), 0.0));
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _indices.push_back(0);
    
    buildVAO ();
    
}

void DrawPoint::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}



void DrawPoint::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}