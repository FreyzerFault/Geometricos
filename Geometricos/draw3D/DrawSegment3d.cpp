
#include "DrawSegment3d.h"


GEO::DrawSegment3d::DrawSegment3d (Segment3d &t): dt (t), Draw(){
    
    _vertices.push_back ( glm::vec3 (dt.getOrigin().getX(), dt.getOrigin().getY() , dt.getOrigin().getZ() ) );
    _vertices.push_back ( glm::vec3 (dt.getDestination().getX(), dt.getDestination().getY() , dt.getDestination().getZ() ) );
    
    
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    

    _indices.push_back ( 0 );
    _indices.push_back ( 1 );
    

    buildVAO ();
    
}


void GEO::DrawSegment3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawSegment3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::LINE );
    Scene::getInstance ()->addModel ( this );
}

