

#include "DrawTriangle3d.h"


GEO::DrawTriangle3d::DrawTriangle3d (Triangle3D &t): dt (t), Draw(){
    
    _vertices.push_back ( glm::vec3 (dt._a.getX(), dt._a.getY() , dt._a.getZ() ) );
    _vertices.push_back ( glm::vec3 (dt._b.getX(), dt._b.getY() , dt._b.getZ() ) );
    _vertices.push_back ( glm::vec3 (dt._c.getX(), dt._c.getY() , dt._c.getZ() ) );
    
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );

    _indices.push_back ( 0 );
    _indices.push_back ( 1 );
    _indices.push_back ( 2 );

    buildVAO ();
    
}


void GEO::DrawTriangle3d::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawTriangle3d::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::WIREFRAME );
    Scene::getInstance ()->addModel ( this );
    
}
