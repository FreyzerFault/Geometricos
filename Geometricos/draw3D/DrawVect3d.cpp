#include "DrawVect3d.h"


GEO::DrawVect3d::DrawVect3d (Vec3D &p): dp (p), Draw(){
    
    _vertices.push_back (glm::vec3(p.getX(), p.getY(), p.getZ()));
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _indices.push_back(0);
    
    buildVAO ();
    
}

void GEO::DrawVect3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}



void GEO::DrawVect3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POINT );
    Scene::getInstance ()->addModel ( this );
    
}
