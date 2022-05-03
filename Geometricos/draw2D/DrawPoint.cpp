#include "DrawPoint.h"
#include "Scene.h"


GEO::DrawPoint::DrawPoint (const Point &p): Draw(), dp (p){
    

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