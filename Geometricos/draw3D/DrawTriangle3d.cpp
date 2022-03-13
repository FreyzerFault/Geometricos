#include "DrawTriangle3D.h"


GEO::DrawTriangle3D::DrawTriangle3D (const Triangle3D &triangle): Draw(), dt (triangle){
    
    _vertices.emplace_back(triangle._a.getX(), triangle._a.getY() , triangle._a.getZ());
    _vertices.emplace_back(triangle._b.getX(), triangle._b.getY() , triangle._b.getZ());
    _vertices.emplace_back(triangle._c.getX(), triangle._c.getY() , triangle._c.getZ());

    const Vec3D n = triangle.normal();

    _normals.emplace_back(n.getX(), n.getY(), n.getZ());
    _normals.emplace_back(n.getX(), n.getY(), n.getZ());
    _normals.emplace_back(n.getX(), n.getY(), n.getZ());

    _indices.push_back (0);
    _indices.push_back (1);
    _indices.push_back (2);

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
