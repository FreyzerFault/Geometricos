
#include "DrawSegment.h"


GEO::DrawSegment::DrawSegment (SegmentLine &t): dt (t), Draw(){
    
    _vertices.push_back ( glm::vec3 (dt._orig.getX(), dt._orig.getY() , 0.0 ) );
    _vertices.push_back ( glm::vec3 (dt._dest.getX(), dt._dest.getY() , 0.0 ) );
    
    
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    

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
