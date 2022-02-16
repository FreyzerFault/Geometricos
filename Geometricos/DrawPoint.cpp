
/* 
 * File:   DrawPoint.cpp
 * Author: lidia
 * 
 * Created on 14 de enero de 2021, 15:02
 */

#include "DrawPoint.h"


GEO::DrawPoint::DrawPoint (Point &p): dp (p), Draw(){
    

    _vertices.emplace_back(p.getX(), p.getY(), 0.0);
    _normals.emplace_back(0, 0, 1);
    _indices.push_back(0);
    
    buildVAO ();
    
}

void GEO::DrawPoint::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}



void GEO::DrawPoint::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}