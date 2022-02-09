
#include "Scene.h"
#include "DrawTriangle.h"


DrawTriangle::DrawTriangle (Triangle &t): dt (t), Draw(){
    
    _vertices.push_back ( glm::vec3 (dt.a.getX(), dt.a.getY() , 0.0 ) );
    _vertices.push_back ( glm::vec3 (dt.b.getX(), dt.b.getY() , 0.0 ) );
    _vertices.push_back ( glm::vec3 (dt.c.getX(), dt.c.getY() , 0.0 ) );
    
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
    _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );

    _indices.push_back ( 0 );
    _indices.push_back ( 1 );
    _indices.push_back ( 2 );

    buildVAO ();
    
}


void DrawTriangle::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawTriangle::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::WIREFRAME );
    Scene::getInstance ()->addModel ( this );
    
}