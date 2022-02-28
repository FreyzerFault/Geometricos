
#include "Scene.h"
#include "DrawTriangle.h"


GEO::DrawTriangle::DrawTriangle (const Triangle& triangle): Draw(), _triangle (triangle){
    
    _vertices.emplace_back(_triangle.a.getX(), _triangle.a.getY() , 0.0);
    _vertices.emplace_back(_triangle.b.getX(), _triangle.b.getY() , 0.0);
    _vertices.emplace_back(_triangle.c.getX(), _triangle.c.getY() , 0.0);
    
    _normals.emplace_back(0, 0, 1);
    _normals.emplace_back(0, 0, 1);
    _normals.emplace_back(0, 0, 1);

    _indices.push_back ( 0 );
    _indices.push_back ( 1 );
    _indices.push_back ( 2 );

    buildVAO ();
}


void GEO::DrawTriangle::drawIt (const TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawTriangle::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::WIREFRAME );
    Scene::getInstance ()->addModel ( this );
    
}