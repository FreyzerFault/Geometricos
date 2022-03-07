#include "DrawTriangle3D.h"


GEO::DrawTriangle3D::DrawTriangle3D (const Triangle3D &triangle): Draw(), dt (triangle){
    
    _vertices.emplace_back(dt._a.getX(), dt._a.getY() , dt._a.getZ());
    _vertices.emplace_back(dt._b.getX(), dt._b.getY() , dt._b.getZ());
    _vertices.emplace_back(dt._c.getX(), dt._c.getY() , dt._c.getZ());

    const Vec3D n = triangle.normal();

    _normals.emplace_back(n.getX(), n.getY(), n.getZ());
    _normals.emplace_back(n.getX(), n.getY(), n.getZ());
    _normals.emplace_back(n.getX(), n.getY(), n.getZ());

    _indices.push_back ( 0 );
    _indices.push_back ( 1 );
    _indices.push_back ( 2 );

    buildVAO ();
    
}


void GEO::DrawTriangle3D::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawTriangle3D::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::WIREFRAME );
    Scene::getInstance ()->addModel ( this );
    
}
