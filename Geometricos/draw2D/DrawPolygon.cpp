#include "DrawPolygon.h"
#include "Polygon.h"
#include "Scene.h"


GEO::DrawPolygon::DrawPolygon (Polygon &polygon): Draw(), _polygon(&polygon){
    
    for (int i=0; i < _polygon->getNumVertices(); i++){
        
        Point aux = _polygon->getVertexAt(i).getPoint();
    
        _vertices.emplace_back(aux.getX(), aux.getY(), 0);
        _normals.emplace_back(0, 0, 1);
        _indices.push_back ( i );
    }

    buildVAO ();
}


void GEO::DrawPolygon::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawPolygon::drawIt (){
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::PolygonGeo );
    Scene::getInstance ()->addModel ( this );
    
}
