#include "DrawTDelaunay.h"

GEO::DrawTDelaunay::DrawTDelaunay(const TDelaunay& delaunay) : delaunay(delaunay) {

    delaunay
    drawTriangles->addVertices();
    
}

void GEO::DrawTDelaunay::drawIt(TypeColor c) {
    drawTriangles->setColorActivo(c);
    drawIt();
}



void GEO::DrawTDelaunay::drawIt() {
    drawTriangles->setShaderProgram("algeom");
    drawTriangles->setDrawMode(TypeDraw::WIREFRAME);
    Scene::getInstance()->addModel(drawTriangles);

}
