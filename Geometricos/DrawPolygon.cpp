

#include "DrawPolygon.h"
#include "PolygonGeo.h"


DrawPolygon::DrawPolygon (PolygonGeo &t): dt (t), Draw(){
    
    for (int i=0; i<dt.getNumVertices(); i++){
        
        Point aux = dt.getVertexAt(i).getPoint();
    
        _vertices.push_back(glm::vec3 (aux.getX(), aux.getY(), 0));
     
        _normals.push_back ( glm::vec3 ( 0, 0, 1 ) );
     
        _indices.push_back ( i );
    }

    buildVAO ();
    
}


void DrawPolygon::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void DrawPolygon::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::PolygonGeo );
    Scene::getInstance ()->addModel ( this );
    
}
