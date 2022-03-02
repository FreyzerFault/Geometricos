#include "DrawSegment.h"

#include "Scene.h"


GEO::DrawSegment::DrawSegment (const SegmentLine &t): Draw(), dt (t){
    
    _vertices.emplace_back(dt._orig.getX(), dt._orig.getY() , 0.0);
    _vertices.emplace_back(dt._dest.getX(), dt._dest.getY() , 0.0);
    
    
    _normals.emplace_back(0, 0, 1);
    _normals.emplace_back(0, 0, 1);
    

    _indices.push_back ( 0 );
    _indices.push_back ( 1 );
    

    buildVAO ();
    
}


void GEO::DrawSegment::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawSegment::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}
