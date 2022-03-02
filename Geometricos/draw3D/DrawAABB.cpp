

#include "DrawAABB.h"
#include "DrawSegment3d.h"


GEO::DrawAABB::DrawAABB (AABB &t): _aabb (t), Draw(){
    
    //XXXX


    buildVAO ();
    
}


void GEO::DrawAABB::drawIt (TypeColor c){
    setColorActivo (c);
    drawIt();
}


void GEO::DrawAABB::drawIt (){
    
    setShaderProgram ( "algeom" );
    setDrawMode(TypeDraw::POLYGON );
    Scene::getInstance ()->addModel ( this );
    
//    for (int i=0; i<dsegment.size(); i++)
//        dsegment[i].drawIt();
    
}

